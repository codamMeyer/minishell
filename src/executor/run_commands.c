#include <libft.h>
#include <signals/signals.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <commands/echo_utils.h>
#include <executor/run_commands.h>
#include <executor/executor_utils.h>
#include <parser/dispatcher.h>


static void	clean_executor_pipes(t_multi_pipes *pipes, int current_process)
{
	if (current_process != FIRST_PROCESS)
		close(pipes->previous[READ_FD]);
	close(pipes->current[WRITE_FD]);
}

/*
	Creates a process for each command 
	Important check that all fd's are closed at the end
	Important!!! Check that there are more than one 
	processes when creating pipes
*/
static int	run_multi_processes(char *env[],
	t_command commands[], int num_of_processes, int *pids)
{
	t_multi_pipes	pipes;
	int				i;

	i = 0;
	while (num_of_processes > 0 && i < num_of_processes)
	{
		pids[i] = create_new_process(&pipes);
		if (pids[i] == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes,
				&commands[i]);
			exit(dispatch_command(&commands[i], env));
		}
		clean_executor_pipes(&pipes, i);
		previous_to_current_pipe(&pipes);
		i++;
	}
	return (SUCCESS);
}

static t_bool	is_env_command(t_command_code code)
{
	return (code == EXPORT || code == UNSET || code == ENV || code == CD);
}

static t_bool	is_single_command(int num_of_cmds, t_command_code code)
{
	return (num_of_cmds == 1 && (code == EXIT || is_env_command(code)));
}

/*
	add redirection for single command
	if file doesn't exist, exit command immediately
	IMPORTANT! check when dispatching only one command
*/
t_exit_code	run_commands(t_command commands[],
				int num_of_commands, char *env[])
{
	int			pids[MAX_CMDS_PER_LINE];
	t_exit_code	exit_status;
	set_signals_during_processes();
	if (is_single_command(num_of_commands, commands[0].code))
	{
		redirect_in_and_output(NULL, 0, 0, &commands[0]);
		exit_status = dispatch_command(&commands[0], env);
	}
	else
	{
		run_multi_processes(env, commands, num_of_commands, &pids[0]);
		exit_status = wait_for_all_processes(num_of_commands, &pids[0]);
	}	
	return (exit_status);
}
