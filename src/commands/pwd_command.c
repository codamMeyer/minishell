#include <libft.h>
#include <commands/commands.h>

t_exit_code	pwd_command(t_command command, t_output_stdout output)
{
	command.arg.start = getcwd(NULL, 0); // SYS_ERROR 1 (shouldn't exit)
	if (!command.arg.start)
		return (ERROR);
	output(command.arg.start);
	output("\n");
	free((char *)command.arg.start);
	return (SUCCESS);
}
