#include "run_commands.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "executor_utils.h"
#include <libft.h>
#include <parser/dispatcher.h>
#include <commands/echo_utils.h>

void	create_table(t_command commands[], char *arg, char *path)
{
	commands->arg.start = arg;
	commands->arg_len = strlen(arg);
	commands->exe_path = path;
}

/*
	Creates a process for each command 
	Important check that all fd's are closed at the end
	Important!!! Check that there are more than one 
	processes when creating pipes
*/
int	run_multi_processes(char *env[],
	t_command commands[], int num_of_processes)
{
	t_multi_pipes	pipes;
	int				process_id;
	int				i;

	i = 0;
	printf("ENTERING EXECUTOR\n");
	while (num_of_processes > 0 && i < num_of_processes)
	{
		process_id = create_new_process(&pipes);
		if (process_id == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes,
				&commands[i]);
			exit(dispatch_command(&commands[i], env));
		}
		if (i != FIRST_PROCESS)
			close(pipes.previous[READ_FD]);
		close(pipes.current[WRITE_FD]);
		previous_to_current_pipe(&pipes);
		i++;
	}
	return (SUCCESS);
}

static t_bool	is_env_command(t_command_code code)
{
	return (code == EXPORT || code == UNSET || code == ENV);
}

t_bool	is_single_command(int num_of_cmds, t_command_code code)
{
	return (num_of_cmds == 1 && (code == EXIT || is_env_command(code)));
}

/*
	add redirection for single command
	if file doesn't exist, exit command immediately
	IMPORTANT! check when dispatching only one command
*/
int	run_commands(t_command commands[],
				int num_of_commands, char *env[])
{
	if (is_single_command(num_of_commands, commands[0].code))
	{
		redirect_in_and_output(NULL, 0, 0, &commands[0]);
		dispatch_command(&commands[0], env);
	}
	else
	{
		run_multi_processes(env, commands, num_of_commands);
		wait_for_all_processes(num_of_commands);
	}
	return (1);
}
