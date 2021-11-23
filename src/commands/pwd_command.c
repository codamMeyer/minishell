#include <libft.h>
#include <env/environment.h>
#include <commands/commands.h>

char	*get_pwd(char *buffer)
{
	const t_env	*pwd = find_variable(get_environment(), "PWD");

	getcwd(buffer, BUFFER_SIZE);
	if (!*buffer && !pwd)
		return (NULL);
	else if (!*buffer && pwd && pwd->value)
		ft_strlcpy(buffer, pwd->value, ft_strlen(pwd->value) + 1);
	return (buffer);
}

t_exit_code	pwd_command(t_command command, t_output_stdout output)
{
	t_buffer	buffer;

	(void)command;
	init_buffer(&buffer);
	if (!get_pwd(buffer.buf))
		return (ERROR);
	output(buffer.buf);
	output("\n");
	return (SUCCESS);
}
