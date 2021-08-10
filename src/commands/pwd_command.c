#include <commands/commands.h>
#include <unistd.h>
#include <libft.h>

int	pwd_command(t_output_stdout output)
{
	char	buffer[2048];
	int		len;

	getcwd(&buffer[0], 2048);
	len = ft_strlen(buffer);
	buffer[len] = '\n';
	output(&buffer[0], len + 1);
	return (SUCCESS);
}
