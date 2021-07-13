#include "parser.h"
#include <string.h>

t_bool	parse_input(const char *input)
{
	t_command	command;

	if (!input)
		return (FALSE);
	command = get_command(input);
	if (command == INVALID)
		return (FALSE);
	return (TRUE);
}

t_command	get_command(const char *input)
{
	if (strncmp(input, ECHO_STR, strlen(ECHO_STR)) == 0)
		return (ECHO);
	return (INVALID);
}
