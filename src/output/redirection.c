#include <output/handle_pipes.h>
#include <unistd.h> 
#include <stdio.h>

void	current_to_previous_pipe(t_multi_pipes *pipes)
{
	pipes->previous[READ_FD] = pipes->current[READ_FD];
	pipes->previous[WRITE_FD] = pipes->current[WRITE_FD];
}

void	set_stdout(int new_std_out)
{
	if (dup2(new_std_out, STDOUT_FILENO) == SYS_ERROR)
		handle_errors(9, "redirect, setting child output");
}

void	set_stdin(int new_std_in)
{
	if (dup2(new_std_in, STDIN_FILENO) == SYS_ERROR)
		handle_errors(9, "redirect, setting child input");
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process)
{
	close(pipes->current[READ_FD]);
	close(pipes->previous[WRITE_FD]);
	if (process != FIRST_PROCESS)
		set_stdin(pipes->previous[READ_FD]);
	if (process != last_process - 1)
		set_stdout(pipes->current[WRITE_FD]);
}
