#include <commands/commands.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>

static void	append_new_line(char *output)
{
	const int	len = ft_strlen(output);

	output[len] = '\n';
}

int	pwd_command(t_output_stdout output)
{
	const char	*buffer = getcwd(NULL, 0);

	if (!buffer)
		return (ERROR);
	append_new_line(buffer);
	output(&buffer[0], ft_strlen(buffer));
	free((char *)buffer);
	return (SUCCESS);
}

