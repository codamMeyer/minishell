#include <parser/dispatcher.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <executor/executor_utils.h>

t_exit_code	unknown_command(t_command command, t_output_stdout output)
{
	const char	*shell_name = "BestShellEver: ";
	const char	*command_not_found = ": command not found\n";

	if (command.files.in != FILE_ERROR)
	{
		output(shell_name);
		output(command.arguments[0]);
		output(command_not_found);
	}
	return (UNKNOWN_COMMAND_ERROR);
}

t_exit_code	empty_command(t_command command, t_output_stdout write_to_stdout)
{
	(void)command;
	(void)write_to_stdout;
	return (SUCCESS);
}

t_exit_code	dispatch_command(t_command *command)
{
	t_buffer							buffer;
	static const t_command_function		functions[LAST] = {
															empty_command,
															echo_command,
															exit_command,
															pwd_command,
															export_command,
															unset_command,
															env_command,
															cd_command,
															unknown_command,
															};

	init_buffer(&buffer);
	if (command->files.in == FILE_ERROR || command->files.out == FILE_ERROR)
		return (ERROR);
	if (command->code == SYSTEM)
		execute_system_command(command);
	else if (command->code == INVALID)
		return (functions[command->code](*command, write_to_stderr));
	return (functions[command->code](*command, write_to_stdout));
}
