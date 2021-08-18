#include <libft.h>
#include <sys/stat.h>
#include <stdio.h>

/*
	command format for now = "/ls", including the backslash
	probably gonna need to strjoin that on there.

	getenv(=PATH) returns a string like this: "/bin;usr/bin;usr/sbin;/sbin"

	which is then split on colons
	I loop through each seperated path to see if it can be accessed with stat() which returns 0 on success otherwise -1
*/

char	*get_executable_path(const char *command)
{
	const char	**all_paths = (const char **)ft_split(getenv("PATH="), ':');
	char		*executable_path;
	int			i;
	struct	stat	buf;

	if (!command)
		return (NULL);
	i = 0;
	executable_path = NULL;
	while (all_paths[i])
	{
		executable_path = ft_strjoin(all_paths[i], command);
		if (executable_path && stat(executable_path, &buf) == 0)
			return (executable_path);
		free(executable_path);
		i++;
	}
	return (NULL);
}
