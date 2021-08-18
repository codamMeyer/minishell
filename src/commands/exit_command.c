#include <commands/commands.h>
#include <stdlib.h>
#include <stdio.h>

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout)
{
	(void)command;
	(void)write_to_stdout;
	exit(SUCCESS); // parse argument to get return code
	return (SUCCESS);
}
