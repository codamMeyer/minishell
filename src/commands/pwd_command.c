#include <commands/commands.h>
#include <unistd.h>
#include <libft.h>
#include <stdio.h>

int	pwd_command(t_output_stdout output)
{
	char	buffer[4096];
	int		len;

	getcwd(&buffer[0], sizeof(buffer));
	len = ft_strlen(buffer);
	buffer[len] = '\n';
	output(&buffer[0], len + 1);
	return (SUCCESS);
}
