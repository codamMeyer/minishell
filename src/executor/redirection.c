#include <executor/redirection.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

void	get_file_name(char *buffer, char **input_ptr)
{
	const int	file_len = get_arg_len(*input_ptr, SPECIALS);
	int			len_to_cpy;

	ft_bzero(&buffer[0], BUFSIZ);
	if (**input_ptr == DOUBLE_QUOTES)
	{
		++(*input_ptr);
		len_to_cpy = file_len - 2;
	}
	else
		len_to_cpy = file_len;
	ft_strlcpy(&buffer[0], *input_ptr, len_to_cpy + 1);
	*input_ptr += file_len;
}

void	handle_infile(char **file_name_ptr, int *in_file)
{
	char	buffer[BUFSIZ];
	int		fd;

	++(*file_name_ptr);
	skip_spaces((const char **)file_name_ptr);
	get_file_name(&buffer[0], file_name_ptr);
	fd = open(buffer, O_RDONLY, 0644);
	if (fd == SYS_ERROR)
		handle_errors(SYS_ERROR, "handle_infile_open");
	if (dup2(fd, STDIN_FILENO) == SYS_ERROR)
		handle_errors(SYS_ERROR, "handle_infile_dup2");
	*in_file = fd;
	close(fd);
}

void	handle_outfile(char **file_name_ptr, int *outfile)
{
	char	buffer[BUFSIZ];
	int		fd;

	++(*file_name_ptr);
	skip_spaces((const char **)file_name_ptr);
	get_file_name(&buffer[0], file_name_ptr);
	fd = open(&buffer[0], O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == SYS_ERROR)
		handle_errors(SYS_ERROR, "handle_outfile_open");
	if (dup2(fd, STDOUT_FILENO) == SYS_ERROR)
		handle_errors(SYS_ERROR, "handle_outfile_dup2");
	*outfile = fd;
	close(fd);
}

/*
	build a check to see if it's a valid file string cat -e main.c >1 >2>3>4
	and add heredoc
		// if (ft_strncmp(&cmd_str[i], "<<", 2)) 
		// 	return ;
		// else (ft_strncmp(&cmd_str[i], ">>", 2))
		// 	return ;
*/
void	handle_files(char *cmd_str, int fd[])
{
	const int	len = get_arg_len(cmd_str, "|");
	char		buffer[BUFSIZ];
	char		*cursor;

	ft_strlcpy(&buffer[0], cmd_str, len + 1);
	check_cmd_str_validity(&buffer[0]);
	cursor = &buffer[0];
	while (cursor && *cursor)
	{
		if (*cursor == LEFT_ANGLE)
			handle_infile(&cursor, &fd[READ_FD]);
		if (*cursor == RIGHT_ANGLE)
			handle_outfile(&cursor, &fd[WRITE_FD]);
		if (*cursor != RIGHT_ANGLE && *cursor != LEFT_ANGLE)
			++cursor;
	}
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, const char *cmd_string)
{	
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	handle_files((char *)cmd_string, fd);
	if (!pipes)
		return ;
	handle_stdin(fd[READ_FD], pipes, process);
	handle_stdout(fd[WRITE_FD], pipes, process, last_process);
	close(pipes->current[READ_FD]);
	if (process != FIRST_PROCESS)
		close(pipes->previous[WRITE_FD]);
}
