#include <commands/commands.h>
#include <env/environment.h>
#include <parser/parser.h>

t_exit_code	export_command(t_command command, t_output_stdout output)
{
	(void)output;
	skip_spaces(&command.arg.start);
	export(get_environment(), command.arg.start);
	return (SUCCESS);
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
	display(get_environment(), output);
	return (SUCCESS);
}
