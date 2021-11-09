#include <commands/commands.h>
#include <env/environment.h>
#include <env/sort_env.h>
#include <parser/parser.h>
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
	skip_spaces(&command.arg.start);
	unset(get_environment(), command.arg.start);
	return (SUCCESS);
}

t_exit_code	env_command(t_command command, t_output_stdout output)
{
	skip_spaces(&command.arg.start);
	display_env(get_environment(), output);
	return (SUCCESS);
}
