#include "handle_pipes.h"
// #include <commands/commands.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "../../libft/libft.h"

/*
	assuming the full unknown command is passed with full checked executable
	path as this is already checked when parsing to see if given
	command is valid ex:
		commands->arg->start = "...[c]at -e main..."
		command->arg->end = "...cat -e mai[n]..."
		command->exe_path = "/bin/cat"
*/

int	execute_command(const char *path, const char *argv[], const char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

void	create_table(t_command commands[], char *arg, char *path)
{
	commands->arg.start = arg;
	commands->arg_len = strlen(arg);
	commands->exe_path = path;
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process, int num_of_processes)
{
	if (process != FIRST_PROCESS)
		set_stdin(pipes->previous[READ_FD], -5);
	if (process != num_of_processes - 1)
		set_stdout(pipes->current[WRITE_FD], pipes->current[READ_FD]);
}

int	*run_forked_processes(t_command commands[], const char *env[], int num_of_processes)
{
	t_multi_pipes	pipes;
	int				*pid;
	int				i;

	pid = (int *)ft_calloc((num_of_processes + 1), sizeof(int));
	if (!pid)
		return (2);
	i = 0;
	while (i < num_of_processes)
	{
		pid[i] = create_new_process(&pipes);
		if (pid[i] == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes);
			child(commands, env, i);
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

	pid = run_forked_processes(commands, num_of_commands, env);
	wait_for_all_processes(pid, num_of_commands);
	free(pid);
	return (1);
}

int main(const int argc, const char *argv[], const char *env[])
{
	t_command commands[MAX_CMDS_PER_LINE];
	int number_of_commands = 3;

	create_table(&commands[0], "cat main", "/bin/cat");
	create_table(&commands[1], "grep int", "/usr/bin/grep");
	create_table(&commands[2], "cat -e", "/bin/cat");
	handle_pipes(commands, number_of_commands, env);
	return (0);
}
