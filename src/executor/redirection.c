#include <executor/redirection.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <libft.h>
#include <unistd.h> 
#include <stdio.h>
#include <fcntl.h>

void	redirect_in_and_output(t_multi_pipes *pipes, int process,
	int last_process, t_command *command)
{	
	if (!pipes)
		return ;
	handle_stdin(command->files.in, pipes, process);
	handle_stdout(command->files.out, pipes, process, last_process);
	if (process != FIRST_PROCESS)
		close(pipes->previous[WRITE_FD]);
	close(pipes->current[READ_FD]);
}
