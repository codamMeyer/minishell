#include "parser.h"
#include <string.h>
#include <ctype.h>

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
	if (is_command(*input, ECHO_STR))
	{
		*input += strlen(ECHO_STR);
		return (ECHO);
	}
	return (INVALID);
}
