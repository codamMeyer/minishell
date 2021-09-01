#include "handle_pipes.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "pipe_utils.h"
#include "../../libft/libft.h"
#include <parser/dispatcher.h>
#include <commands/echo_utils.h>

void	create_table(t_command commands[], char *arg, char *path)
{
	commands->arg.start = arg;
	commands->arg_len = strlen(arg);
	commands->exe_path = path;
}

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
			redirect_in_and_output(&pipes, i, num_of_processes,
				&commands[i].files);
			dispatch_command(&commands[i], env);
		}
		if (i != FIRST_PROCESS)
			close(pipes.previous[READ_FD]);
		close(pipes.current[WRITE_FD]);
		current_to_previous_pipe(&pipes);
		i++;
	}
	return (SUCCESS);
}

int	handle_pipes(t_command commands[],
				int num_of_commands, const char *env[])
{
	if (commands[num_of_commands - 1].code == EXIT)
		exit_command(commands[0], write_to_stdout);
	run_multi_processes(env, commands, num_of_commands);
	wait_for_all_processes(num_of_commands);
	return (1);
}
