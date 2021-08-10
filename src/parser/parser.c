#include <parser/parser.h>
#include <parser/dispatcher.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

static t_bool	is_valid_last_char(char last_char)
{
	return (isspace(last_char) || last_char == '\0');
}

static t_bool	is_command(const char *input, const char *command)
{
	const int		command_len = strlen(command);
	const char		last_char = input[command_len];

	return (strncmp(input, command, command_len) == 0
		&& is_valid_last_char(last_char));
}

t_command	parse_command(const char **input)
{
	static const char	*commands[LAST] = {
											"echo",
											"exit",
											"pwd",
											"",
											"invalid"
										};
	t_command			command_code;

	skip_spaces(input);
	command_code = ECHO;
	while (command_code < INVALID)
	{
		if (is_command(*input, commands[command_code]))
		{
			advance_pointer(input, commands[command_code]);
			return (command_code);
		}
		++command_code;
	}
	return (INVALID);
}

t_bool	parse_input(const char *input)
{
	if (!input)
		return (FALSE);
	dispatch_commands(&input, parse_command(&input));
	return (TRUE);
}
