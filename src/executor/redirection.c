#include <libft.h>
#include <executor/run_commands.h>
#include <parser/parse_redirection.h>
#include <errno.h>

void	restore_std_fds(t_std_fd fds)
{
	if (dup2(fds.in, STDIN_FILENO) == SYS_ERROR || \
		dup2(fds.out, STDOUT_FILENO) == SYS_ERROR)
		handle_error(DUP_ERROR, NULL, DUP2_STR);
	handle_error(close(fds.in), CLOSE_STR, NULL);
	handle_error(close(fds.out), CLOSE_STR, NULL);
}

t_std_fd	save_std_fds(void)
{
	t_std_fd	fds;

	fds.in = dup(STDIN_FILENO);
	fds.out = dup(STDOUT_FILENO);
	if (!fds.in || !fds.out)
		handle_error(DUP_ERROR, NULL, DUP_STR);
	return (fds);
}

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, t_command *command)
{
	handle_stdin(command->files.in, pipes, process);
	handle_stdout(command->files.out, pipes, process, last_process);
	if (!pipes)
		return ;
	if (process != FIRST_PROCESS)
		handle_error(close(pipes->previous[WRITE_FD]), CLOSE_STR, NULL);
	if (process != last_process - 1)
		handle_error(close(pipes->current[READ_FD]), CLOSE_STR, NULL);
}
