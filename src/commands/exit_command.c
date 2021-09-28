#include <libft.h>
#include <stdlib.h>
#include <commands/commands.h>
#include <parser/parser.h>


t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout)
{
	t_exit_code	exit_code;

	(void)write_to_stdout;
	skip_spaces(&command.arg.start);
	exit_code = ft_atoi(command.arg.start);
	exit(exit_code);
	return (exit_code);
}
