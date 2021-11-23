#include <commands/commands.h>
#include <env/environment.h>
#include <env/sort_env.h>
#include <output/write_to_std.h>
#include <stdio.h>

t_exit_code	export_command(t_command command, t_output_stdout output)
{
	(void)output;
	if (!command.arguments[1])
	{
		display_sorted_env();
		return (SUCCESS);
	}
	return (export(get_environment(), command.arguments));
}

t_exit_code	unset_command(t_command command, t_output_stdout output)
{
	(void)output;
	if (!command.arguments[1])
		return (SUCCESS);
	unset(get_environment(), command.arguments);
	return (SUCCESS);
}

t_exit_code	env_command(t_command command, t_output_stdout output)
{
	const char	*error_message = "BestShellEver: env arguments not suported\n";

	(void)command;
	if (command.arguments[1])
	{
		write_to_stderr(error_message);
		return (ERROR);
	}
	display_env(get_environment(), output);
	return (SUCCESS);
}
