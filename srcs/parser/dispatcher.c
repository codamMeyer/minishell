#include "dispatcher.h"

int exit_command()
{
	return (TRUE);
}

t_bool	dispatch_commands(const char **input, t_command command)
{
	(void)input;
	if (command == EXIT)
		return (exit_command());
	return (FALSE);
}