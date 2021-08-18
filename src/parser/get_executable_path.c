#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <parser/get_executable_path.h>

static void	append_command_to_path(char	*buffer, const char *command)
{
	const int	cmd_len = ft_strlen(command) + TERMINATOR;

	*buffer = FORWARD_SLASH;
	buffer += 1;
	ft_strlcpy(buffer, command, cmd_len);
}

static int	get_sub_path_len(const char *path)
{
	int	i;

	i = 0;
	while (path && path[i] != '\0' && path[i] != COLON)
		i++;
	return (i);
}

static void	get_single_path(const char *all_paths, char *buffer, int size)
{
	ft_strlcpy(buffer, all_paths, size + TERMINATOR);
}

int	is_executable(char *full_path_executable, struct stat *status)
{
	return (stat(full_path_executable, status));
}

char	*get_executable_path(const char *command)
{
	const char	*all_paths = getenv(PATH);
	char		*executable_buffer;
	int			single_path_len;
	struct stat	status;

	executable_buffer = calloc(CMD_BUFFER_SIZE, sizeof(char));
	if (!executable_buffer || !command || !all_paths)
		return (NULL);
	while (*all_paths)
	{
		single_path_len = get_sub_path_len(all_paths);
		get_single_path(all_paths, executable_buffer, single_path_len);
		if (single_path_len != (int)ft_strlen(executable_buffer))
			printf("Not sure if the error check is unnecesary?\n");
		append_command_to_path(&executable_buffer[single_path_len], command);
		if (is_executable(executable_buffer, &status) == F_OK)
			return (executable_buffer);
		all_paths += single_path_len + 1;
	}
	return (NULL);
}
