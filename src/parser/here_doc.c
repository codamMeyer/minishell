#include <fcntl.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <executor/executor_utils.h>
#include <parser/parse_redirection.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signals/signals.h>

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
static t_exit_code	append_line_to_heredoc(char *line,
		const char *delimeter, int fd)
{
	if (!line)
		handle_errors(20, "heredoc line read");
	if (is_valid_delimeter(delimeter, line))
		return (ERROR);
	ft_putendl_fd(line, fd);
	return (SUCCESS);
}

static int	cleanup_here_doc(char *line, int fd, char *file_name)
{
	int	*signal;
	int	reopen_fd;

	signal = heredoc_sigint();
	close(fd);
	free(line);
	if (*signal)
	{
		*signal = 0;
		reopen_fd = FILE_ERROR;
	}
	else
		reopen_fd = open(file_name, O_RDONLY, FILE_RIGHTS);
	if (reopen_fd == INVALID_FD)
		handle_errors(19, "here_doc");
	return (reopen_fd);
}

/*
	syntax checker responsible for assuring that this is only entered
	when there is a valid here_doc token
*/
int	handle_here_doc(const char *delimeter)
{
	char		file_name[BUFFER_SIZE];
	int			fd;
	char		*line;
	int			*signal;

	get_file_name(&file_name[0], delimeter);
	fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, FILE_RIGHTS);
	if (fd == INVALID_FD)
		handle_errors(19, "here_doc");
	while (TRUE)
	{
		set_heredoc_signals();
		line = readline("> ");
		signal = heredoc_sigint();
		if (*signal == HERE_DOC_INTERRUPT)
			break ;
		if (!line || append_line_to_heredoc(line, delimeter, fd) == ERROR)
			break ;
		free(line);
	}
	fd = cleanup_here_doc(line, fd, file_name);
	unlink(file_name);
	return (fd);
}
