#include <commands/commands.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>

int	pwd_command(t_output_stdout output)
{
	const char	*buffer = getcwd(NULL, 0);

	if (!buffer)
		return (ERROR);
	output(&buffer[0], ft_strlen(buffer));
	output("\n", 1);
	free((char *)buffer);
	return (SUCCESS);
}
