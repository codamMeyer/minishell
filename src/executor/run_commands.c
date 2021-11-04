#include <libft.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <commands/echo_utils.h>
#include <executor/run_commands.h>
#include <executor/executor_utils.h>
#include <parser/dispatcher.h>
#include <parser/command_table.h>
#include <ctype.h>
#include <parser/parse_redirection.h>
#include <signals/signals.h>

static void	close_pipes(int *pipes_to_close)
{
	handle_error(close(pipes_to_close[READ_FD]), "close()", NULL);
	handle_error(close(pipes_to_close[WRITE_FD]), "close()", NULL);
}

/*
	Creates a process for each command 
	Important check that all fd's are closed at the end
	Important!!! Check that there are more than one 
	processes when creating pipes
*/
int	run_multi_processes(char *env[], t_command commands[],
		int num_of_processes, int *pids)
{
	t_multi_pipes	pipes;
	int				i;

	i = 0;
	while (num_of_processes > 0 && i < num_of_processes)
	{
		pids[i] = create_new_process(&pipes, i, num_of_processes);
		set_child_signals();
		if (pids[i] == CHILD_PROCESS)
		{
			redirect_in_and_output(&pipes, i, num_of_processes,
				&commands[i]);
			exit(dispatch_command(&commands[i], env));
		}
		if (i != FIRST_PROCESS)
			close_pipes(pipes.previous);
		previous_to_current_pipe(&pipes);
		i++;
	}
	return (SUCCESS);
}

static t_bool	is_builtin_command(t_command_code code)
{
	return (code >= EMPTY_LINE && code <= INVALID);
}

t_bool	is_single_command(int num_of_cmds, t_command *command)
{
	t_buffer		buffer;
	t_arg			arg;
	t_command_code	code;
	const char		*inp = &buffer.buf[0];

	if (command->code == INVALID)
	{
		init_buffer(&buffer);
		arg = command->arg;
		while (*arg.start && !ft_isspace(*arg.start))
			append_expanded_input_to_buffer(&arg, &buffer);
		code = get_command_code((const char **)&inp, command);
		return (num_of_cmds == 1 && is_builtin_command(code));
	}
	return (num_of_cmds == 1 && is_builtin_command(command->code));
}

/*
	add redirection for single command
	if file doesn't exist, exit command immediately
	IMPORTANT! check when dispatching only one command
*/
int	run_commands(t_command commands[],
				int num_of_commands, char *env[])
{
	const t_std_fd	fds = save_std_fds();
	const int		*signal = heredoc_sigint();
	t_exit_code		exit_code;
	int				pids[MAX_CMDS_PER_LINE];

	if (*signal)
		return (1);
	if (is_single_command(num_of_commands, &commands[0]))
	{
		redirect_in_and_output(NULL, 0, 0, &commands[0]);
		exit_code = dispatch_command(&commands[0], env);
	}
	else
	{
		run_multi_processes(env, commands, num_of_commands, pids);
		exit_code = wait_for_all_processes(num_of_commands, pids);
	}	
	restore_std_fds(fds);
	return (exit_code);
}
