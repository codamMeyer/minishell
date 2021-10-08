#include <defines.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/commands.h>
#include <env/environment.h>
#include <executor/run_commands.h>

static void	update_env(char *cwd_value)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (!current_directory)
		return ;
	export(get_environment(), "OLDPWD=");
	find_variable(get_environment(), "OLDPWD")->value = cwd_value;
	find_variable(get_environment(), "PWD")->value = current_directory;
}

static void	copy_home_var_to_buffer(char *buffer)
{
	const t_env	*home_var = find_variable(get_environment(), "HOME");
	int			len;

	if (!home_var)
	{
		printf("cd: HOME not set\n");
		return ;
	}
	len = ft_strlen(home_var->value) + 1;
	ft_strlcpy(buffer, home_var->value, len);
}

t_exit_code	cd_command(t_command command, t_output_stdout output)
{
	const t_env	*pwd = find_variable(get_environment(), "PWD");
	char		buffer[BUFFER_SIZE];

	(void)output;
	if (!pwd)
		return (ERROR);
	if (command.arg.len == 0 || *command.arg.start == '~')
		copy_home_var_to_buffer(buffer);
	else
		ft_strlcpy(buffer, command.arg.start, command.arg.len + 1);
	if (chdir(buffer) == SYS_ERROR)
		return (ERROR);
	update_env(pwd->value);
	return (SUCCESS);
}
