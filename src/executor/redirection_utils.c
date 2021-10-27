#include <libft.h>
#include <executor/run_commands.h>
#include <executor/executor_utils.h>
#include <parser/command_table.h>
#include <parser/parse_redirection.h>

void	handle_stdin(int in_file, t_multi_pipes *pipes, int current_process)
{
	if (in_file != INVALID_FD)
	{
		set_stdin(in_file);
		close(in_file); // CLOSE_FD_ERROR ?
	}
	else if (pipes && \
	(current_process != FIRST_PROCESS && in_file == INVALID_FD))
		set_stdin(pipes->previous[READ_FD]);
}

void	handle_stdout(int out_file, t_multi_pipes *pipes, int current_process,
	int last_process)
{
	if (out_file != INVALID_FD)
	{
		set_stdout(out_file);
		close(out_file); // CLOSE_FD_ERROR ?
	}
	else if (pipes && \
	(current_process != last_process - 1 && out_file == INVALID_FD))
		set_stdout(pipes->current[WRITE_FD]);
}

void	previous_to_current_pipe(t_multi_pipes *pipes)
{
	pipes->previous[READ_FD] = pipes->current[READ_FD];
	pipes->previous[WRITE_FD] = pipes->current[WRITE_FD];
}

void	set_stdout(int new_std_out)
{
	if (dup2(new_std_out, STDOUT_FILENO) == SYS_ERROR) // SYS_ERROR (exit ONLY PROCESS ?) DUP2
		handle_errors(9, "redirect, setting child output");
}

void	set_stdin(int new_std_in)
{
	if (dup2(new_std_in, STDIN_FILENO) == SYS_ERROR) // SYS_ERROR (exit ONLY PROCESS ?) DUP2
		handle_errors(9, "redirect, setting child input");
}
