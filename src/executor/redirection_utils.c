#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <../libft/libft.h>

void	handle_stdin(int in_file, t_multi_pipes *pipes, int process)
{
	if (process != FIRST_PROCESS && in_file == -1)
		set_stdin(pipes->previous[READ_FD]);
}

void	handle_stdout(int out_file, t_multi_pipes *pipes, int process,
	int last_process)
{
	if (process != last_process - 1 && out_file == -1)
		set_stdout(pipes->current[WRITE_FD]);
}

void	previous_to_current_pipe(t_multi_pipes *pipes)
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
