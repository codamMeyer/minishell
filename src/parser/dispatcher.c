#include <ctype.h>
#include <libft.h>
#include <stdio.h>
#include <parser/dispatcher.h>
#include <commands/buffer.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <executor/executor_utils.h>
#include <env/env_utils.h>

static void	copy_unknown_command_to_buffer(const char **input, char buffer[])
{
	const char	*cur = *input;
	int			i;

	i = 0;
	while (cur[i] && !ft_isspace(cur[i]))
		++i;
	ft_memcpy(buffer, cur, i);
	buffer[i] = '\0';
}

t_exit_code	unknown_command(t_command command, t_output_stdout output)
{
	const char	*shell_name = "BestShellEver: ";
	const char	*command_not_found = ": command not found\n";
	char		unknown_command_str[4096];

	skip_spaces(&command.arg.start);
	copy_unknown_command_to_buffer(&command.arg.start, &unknown_command_str[0]);
	if (command.files.in != FILE_ERROR)
	{
		output(shell_name);
		output(&unknown_command_str[0]);
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
		return (1);
	// if (command->code == INVALID)
	// 	command = expand_arg_content(command, &buffer);
	if (command->code == SYSTEM)
		execute_system_command(command);
	else if (command->code == INVALID)
		return (functions[command->code](*command, write_to_stderr));
	return (functions[command->code](*command, write_to_stdout));
}
