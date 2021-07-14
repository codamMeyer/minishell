#include "parser.h"
#include <string.h>
#include <ctype.h>

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

static void	advance_pointer(const char **input, const char *command_str)
{
	*input += strlen(command_str);
}

t_command	parse_command(const char **input)
{
	static const char	*commands[LAST] = {"echo", ""};
	t_command			command_code;

	command_code = 0;
	while (command_code != INVALID)
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
	t_command	command_code;

	if (!input)
		return (FALSE);
	command_code = parse_command(&input);
	if (command_code == INVALID)
		return (FALSE);
	return (TRUE);
}
