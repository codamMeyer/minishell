#include <parser/dispatcher.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <parser/parser.h>
#include <stdio.h>
#include <libft.h>
#include <ctype.h>

static void	copy_unknown_command_to_buffer(const char **input, char buffer[])
{
	const char	*cur = *input;
	int			i;

	i = 0;
	while (cur[i] && !isspace(cur[i]))
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
	output(shell_name);
	output(&unknown_command_str[0]);
	output(command_not_found);
	return (SUCCESS);
}

t_exit_code	empty_command(t_command command, t_output_stdout write_to_stdout)
{
	(void)command;
	(void)write_to_stdout;
	return (SUCCESS);
}

t_exit_code	dispatch_commands(const t_command *command_table)
{
	static const t_command_function		functions[LAST] = {
															empty_command,
															echo_command,
															exit_command,
															pwd_command,
															unknown_command,
															};

	functions[command_table->code](*command_table, write_to_stdout);
	exit(SUCCESS);
	return (SUCCESS);
}

/*

t_command_function commands[LAST] = {
										empty_command,
										echo_command,
										exit_command,
										pwd_command,
									}

*/