#include <commands/commands.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <stdlib.h>
#include <../libft/libft.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <stdio.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

/*
	Assumes that string has been checked for quotes
*/
int	get_file_name_and_length(char *buffer, char *input)
{
	const int	file_name_len = get_arg_len(input, SPECIALS);
	int			len_to_cpy;
	char		*cursor;

	ft_bzero(&buffer[0], BUFFER_SIZE);
	cursor = input;
	if (*cursor == DOUBLE_QUOTES)
	{
		++(cursor);
		len_to_cpy = file_name_len - 2;
	}
	else
		len_to_cpy = file_name_len;
	ft_strlcpy(&buffer[0], cursor, len_to_cpy + 1);
	return (file_name_len);
}

/*
	HERE_DOC
	fork
		open_temporary file "/tmp/filenamekajdiabisbd" o_trunc
			write to that file until delimiter is found
		close
		open again in readonly mode
		unlink
		dup2()
*/

void	get_file_name(char *buffer, const char *delimeter)
{
	const int	path_len = ft_strlen(TMP_FILE_PATH);
	const int	delimiter_len = ft_strlen(delimeter);

	ft_memcpy(buffer, TMP_FILE_PATH, path_len);
	ft_strlcpy(buffer, delimeter, delimiter_len + 1);
}

t_bool	is_valid_delimeter(const char *delimeter, const char *line)
{
	const int	delimeter_len = ft_strlen(delimeter);
	const int	line_len = ft_strlen(line);

	return (delimeter_len == line_len
		&& ft_strncmp(line, delimeter, delimeter_len) == 0);
}

void	handle_here_doc(const char *delimeter, int *in_file)
{
	char		file_name[BUFFER_SIZE];
	int			fd;
	char		*line;

	if (!delimeter)
		return ;
	get_file_name(&file_name[0], delimeter);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		handle_errors(19, "here_doc");
	while (1)
	{
		line = readline("> ");
		if (!line)
			handle_errors(20, "heredoc line read");
		if (is_valid_delimeter(delimeter, line))
			break ;
		ft_putendl_fd(line, fd);
		free(line);
	}
	free(line);
	close(fd);
	*in_file = open(file_name, O_RDONLY, 0664);
	unlink(file_name);
}

/*
	Might still split this into diff functions
*/
void	open_in_mode(const char *file, t_files *files, int mode_id)
{
	if (mode_id == LEFT_ANGLE)
		open_infile(file, &files->in);
	else if (mode_id == RIGHT_ANGLE || mode_id == APPEND)
		open_outfile(file, &files->out, mode_id);
	else if (mode_id == HERE_DOC)
		handle_here_doc(file, &files->in);

}

/*
	i keeps trtack of how many chars need to be
	replaced by spaces
*/
int	open_file(char *file_name_ptr, t_files *files, int redirection_id)
{
	char	buffer[BUFFER_SIZE];
	int		i;

	i = count_consecutive_spaces(file_name_ptr);
	i += get_file_name_and_length(&buffer[0], &file_name_ptr[i]);
	open_in_mode((const char *)buffer, files, redirection_id);
	return (i);
}

/*
	return t_files which have an int for the in and out fd's respectively
*/
t_files	get_redirection(char **input, const int string_to_parse_len)
{
	int		index;
	int		length;
	int		redirect_id;
	t_files	fd;
	char	*cursor;

	fd.in = INVALID_FD;
	fd.out = INVALID_FD;
	cursor = *input;
	index = get_arg_len(&cursor[0], "><") + 1;
	while (index < string_to_parse_len)
	{
		redirect_id = get_redirect_id(&cursor[index - 1]);
		if (redirect_id == APPEND || redirect_id == HERE_DOC)
			index += 1;
		length = open_file(&cursor[index], &fd, redirect_id);
		if (redirect_id == APPEND || redirect_id == HERE_DOC)
			index -= 1;
		replace_redirection_w_space(input, length + 2, index - 1);
		index += get_arg_len(&cursor[index], "><") + 1;
	}
	return (fd);
}

