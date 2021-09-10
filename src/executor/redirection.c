#include <executor/redirection.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

void	handle_stdin(int in_file, t_multi_pipes *pipes, int process)
{
	if (process != FIRST_PROCESS && in_file == -1)
		set_stdin(pipes->previous[READ_FD]);
}

void	handle_stdout(int out_file, t_multi_pipes *pipes, int process,
	int last_process)
{
	if (process != last_process - 1 && out_file == -1)
		set_stdout(pipes->current[WRITE_FD]);
}

void	get_file_name(char *buffer, char **input_ptr)
{
	const int	len = get_cmd_len(*input_ptr);

	ft_bzero(&buffer[0], BUFSIZ);
	ft_strlcpy(&buffer[0], *input_ptr, len + 1);
	*input_ptr += len;
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
	while (cmd_str && *cmd_str && *cmd_str != PIPE)
	{
		if (*cmd_str == LEFT_ANGLE)
			handle_infile(&cmd_str, &fd[READ_FD]);
		else if (*cmd_str == RIGHT_ANGLE)
			handle_outfile(&cmd_str, &fd[WRITE_FD]);
		++cmd_str;
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
