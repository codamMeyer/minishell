#include <fcntl.h>
#include <libft.h>
#include <unistd.h> 
#include <executor/redirection.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <stdio.h>

void	restore_std_fds(t_std_fd fds)
{
	dup2(fds.in, STDIN_FILENO);
	dup2(fds.out, STDOUT_FILENO);
	close(fds.in);
	close(fds.out);
}

t_std_fd	save_std_fds(void)
{
	t_std_fd	fds;

	fds.in = dup(STDIN_FILENO);
	fds.out = dup(STDOUT_FILENO);
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
		close(pipes->previous[WRITE_FD]);
	if (process != last_process - 1)
		close(pipes->current[READ_FD]);
}
