#include <readline/readline.h>
#include <readline/history.h>
#include <executor/executor_utils.h>
#include <parser/parse_redirection.h>
#include <fcntl.h>
#include <stdlib.h>
#include <libft.h>

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
	close(fd);
	free(line);
	*in_file = open(file_name, O_RDONLY, 0664);
	unlink(file_name);
}
