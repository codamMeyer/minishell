#include <readline/readline.h>
#include <readline/history.h>
#include <executor/executor_utils.h>
#include <parser/parse_redirection.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>
#include <stdio.h>

static void	get_file_name(char *buffer, const char *delimeter)
{
	const int	path_len = ft_strlen(TMP_FILE_PATH);
	const int	delimiter_len = ft_strlen(delimeter);

	ft_memcpy(buffer, TMP_FILE_PATH, path_len);
	ft_strlcpy(buffer, delimeter, delimiter_len + 1);
}

static t_bool	is_valid_delimeter(const char *delimeter, const char *line)
{
	const int	delimeter_len = ft_strlen(delimeter);
	const int	line_len = ft_strlen(line);

	return (delimeter_len == line_len
		&& ft_strncmp(line, delimeter, delimeter_len) == 0);
}

/*
	returns an int to indicate if loop shoud stop
*/
static int	append_line_to_heredoc(char *line,
		const char *delimeter, int fd)
{
	if (!line)
		handle_errors(20, "heredoc line read");
	if (is_valid_delimeter(delimeter, line))
		return (ERROR);
	ft_putendl_fd(line, fd);
	return (SUCCESS);
}

void	cleanup_here_doc(char *line, int fd)
{
	close(fd);
	free(line);
}

/*
	syntax checker responsible for assuring that this is only entered
	when ere is a valid here_doc token
*/
int	handle_here_doc(const char *delimeter)
{
	char		file_name[BUFFER_SIZE];
	int			fd;
	char		*line;

	get_file_name(&file_name[0], delimeter);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0664);
	if (fd == INVALID_FD)
		handle_errors(19, "here_doc");
	while (1)
	{
		line = readline("> ");
		if (append_line_to_heredoc(line, delimeter, fd) == ERROR)
			break ;
		free(line);
	}
	cleanup_here_doc(line, fd);
	fd = open(file_name, O_RDONLY, 0664);
	if (fd == INVALID_FD)
		handle_errors(19, "here_doc");
	unlink(file_name);
	return (fd);
}
