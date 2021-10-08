#include <defines.h>
#include <libft.h>
#include <unistd.h>
#include <stdio.h>
#include <commands/commands.h>
#include <env/environment.h>
#include <executor/run_commands.h>

void	update_env(char *cwd_value)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 0);
	if (!current_directory)
		return ;
	export(get_environment(), "OLDPWD=");
	find_variable(get_environment(), "OLDPWD")->value = cwd_value;
	find_variable(get_environment(), "PWD")->value = current_directory;
}

t_exit_code	cd_command(t_command command, t_output_stdout output)
{
	const t_env	*pwd = find_variable(get_environment(), "PWD");
	char		command_buffer[BUFFER_SIZE];

	(void)output;
	if (!pwd)
		return (ERROR);
	ft_strlcpy(command_buffer, command.arg.start, command.arg.len + 1);
	if (chdir(command_buffer) == SYS_ERROR)
		return (ERROR);
	update_env(pwd->value);
	return (SUCCESS);
}
