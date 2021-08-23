#include "handle_pipes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pipe_utils.h"
#include "../../libft/libft.h"
#include <parser/dispatcher.h>

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
*/

int	*run_multi_processes(const char *env[],
	t_command commands[], int num_of_processes)
{
	t_multi_pipes	pipes;
	int				*pid;
	int				i;
	(void)env;
	pid = (int *)ft_calloc((num_of_processes + 1), sizeof(int));
	if (!pid)
		return (NULL);
	i = 0;
	while (i < num_of_processes)
	{
		pid[i] = create_new_process(&pipes);
		if (pid[i] == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes);
			// execute_commands(&commands[i], env);
			dispatch_commands(commands);
		}
		if (i != FIRST_PROCESS)
			close(pipes.previous[READ_FD]);
		close(pipes.current[WRITE_FD]);
		current_to_previous_pipe(&pipes);
		i++;
	}
	return (pid);
}

int	handle_pipes(t_command commands[],
				int num_of_commands, const char *env[])
{
	int	*pid;

	pid = run_multi_processes(env, commands, num_of_commands);
	wait_for_all_processes(pid, num_of_commands);
	free(pid);
	return (1);
}

// int	run_pipes(const char *env[])
// {
// 	t_command	commands[MAX_CMDS_PER_LINE];
// 	const int	number_of_commands = 3;

// 	create_table(&commands[0], "cat main.c", "/bin/cat");
// 	create_table(&commands[1], "grep int", "/usr/bin/grep");
// 	create_table(&commands[2], "cat -e", "/bin/cat");
// 	handle_pipes(commands, number_of_commands, env);
// 	return (0);
// }
