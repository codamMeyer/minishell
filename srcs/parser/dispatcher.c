#include "dispatcher.h"
#include "../commands/commands.h"
#include <stdio.h>

t_bool	dispatch_commands(const char **input, t_command command)
{
	(void)input;
	if (command == EXIT)
		exit_command(SUCCESS);
	return (FALSE);
}