#include "handle_pipes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pipe_utils.h"
#include "../../libft/libft.h"
#include <parser/dispatcher.h>
#include <commands/echo_utils.h>

/*
	assuming the full unknown command is passed with full checked executable
	path as this is already checked when parsing to see if given
	command is valid ex:
		commands->arg->start = "...[c]at -e main..."
		command->arg->end = "...cat -e mai[n]..."
		command->exe_path = "/bin/cat"
*/

void	create_table(t_command commands[], char *arg, char *path)
{
	commands->arg.start = arg;
	commands->arg_len = strlen(arg);
	commands->exe_path = path;
}

/*
	If command_code == valid_different split arguments
	// execute_commands(&commands[i], env) to be place in dispatcher
*/

int	run_multi_processes(const char *env[],
	t_command commands[], int num_of_processes)
{
	t_multi_pipes	pipes;
	int				pid;
	int				i;

	(void)env;
	i = 0;
	while (num_of_processes > 0 && i < num_of_processes)
	{
		pid = create_new_process(&pipes);
		if (pid == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes);
			dispatch_commands(&commands[i]);
		}
		current_to_previous_pipe(&pipes);
		i++;
	}
	return (SUCCESS);
}

int	handle_pipes(t_command commands[],
				int num_of_commands, const char *env[])
{
	if (commands[0].code == EXIT)
		exit_command(commands[0], write_to_stdout);
	run_multi_processes(env, commands, num_of_commands);
	wait_for_all_processes(num_of_commands);
	return (1);
}
