#include <parser/dispatcher.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <parser/parser.h>
#include <stdio.h>
#include <libft.h>
#include <ctype.h>

static void	copy_unknown_command_to_buffer(const char **input, char buffer[])
{
	char	cur;
	int		i;

	i = 0;
	cur = (*input)[i];
	while (cur && !isspace(cur))
	{
		buffer[i] = cur;
		++i;
		cur = (*input)[i];
	}
	buffer[i] = '\0';
}

t_bool	unknown_command(const char **input, t_output_stdout output)
{
	const char	*shell_name = "BestShellEver: ";
	const char	*command_not_found = ": command not found\n";
	char		unknown_command_str[4096];

	skip_spaces(input);
	copy_unknown_command_to_buffer(input, &unknown_command_str[0]);
	output(shell_name);
	output(&unknown_command_str[0]);
	output(command_not_found);
	return (FALSE);
}

t_bool	dispatch_commands(const char **input, t_command command)
{
	if (command == EXIT)
		exit_command(SUCCESS);
	else if (command == ECHO)
		return (echo_command(input, write_to_stdout));
	else if (command == PWD)
		return (pwd_command(write_to_stdout));
	else if (command == INVALID)
		return (unknown_command(input, write_to_stdout));
	else if (command == EMPTY_LINE)
		return (TRUE);
	return (FALSE);
}
