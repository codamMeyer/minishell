#include <libft.h>
#include <executor/run_commands.h>
#include <parser/parse_redirection.h>
#include <errno.h>

void	handle_stdin(int in_file, t_multi_pipes *pipes, int current_process)
{
	if (in_file != FILE_ERROR && in_file != INVALID_FD)
	{
		set_stdin(in_file);
		handle_error(close(in_file), CLOSE_STR, NULL);
	}
	else if (pipes && \
	(current_process != FIRST_PROCESS && in_file == INVALID_FD))
		set_stdin(pipes->previous[READ_FD]);
}

void	handle_stdout(int out_file, t_multi_pipes *pipes, int current_process,
	int last_process)
{
	if (out_file != FILE_ERROR && out_file != INVALID_FD)
	{
		set_stdout(out_file);
		handle_error(close(out_file), CLOSE_STR, NULL);
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
	if (dup2(new_std_out, STDOUT_FILENO) == SYS_ERROR && errno != EBADF)
		handle_error(DUP_ERROR, NULL, DUP2_STR);
}

void	set_stdin(int new_std_in)
{
	if (dup2(new_std_in, STDIN_FILENO) == SYS_ERROR && errno != EBADF)
		handle_error(DUP_ERROR, NULL, DUP2_STR);
}
