#include <parser/dispatcher.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <stdio.h>

t_bool	dispatch_commands(const char **input, t_command command)
{
	(void)input;
	if (command == EXIT)
		exit_command(SUCCESS);
	else if (command == ECHO)
		return (echo_command(input, echo_stdout));
	return (FALSE);
}
