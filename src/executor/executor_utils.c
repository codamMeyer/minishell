#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include <commands/buffer.h>
#include <executor/executor_utils.h>
#include <executor/run_commands.h>

t_exit_code	wait_for_all_processes(int num_of_processes)
{
	t_exit_code exit_code;
	int	i;
	int	status;

	i = 0;
	exit_code = 0;
	while (i < num_of_processes)
	{
		waitpid(DEFAULT_WAIT_ID, &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status);
		i++;
	}
	return (exit_code);
}

/*
	Basic error handeling fucntion to make troubleshooting easier for system calls
*/
void	handle_errors(int error_code, const char *description_location)
{
	perror(description_location);
	exit(error_code);
}

/*
	Done like this to not have confusing typecasting flying around
*/
static int	execute_command(const char *path, char *argv[], char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

void	execute_system_command(const t_command *command, char *env[])
{
	char		**cmd;
	t_buffer	buffer;

	init_buffer(&buffer);
	while (command->arg.start < command->arg.end)
		append_expanded_input_to_buffer((t_arg *)&command->arg, &buffer);
	cmd = ft_split(&buffer.buf[0], SPACE_CHAR);
	if (!cmd)
		handle_error(MALLOC_ERROR, NULL);
	if (execute_command(command->exe_path, cmd, env) == SYS_ERROR)
		handle_error(SYS_ERROR, "child_process");
}

/*
	Calls pipe() first so that the pipe fds are accesible in
	the main as well as in the child process
*/
int	create_new_process(t_multi_pipes *pipes,
		int current_process, int num_of_process)
{
	const int	process_limit = num_of_process - 1;
	int			process_id;

	if (current_process != process_limit && pipe(pipes->current) == SYS_ERROR)
		handle_errors(7, "pipe current main");
	process_id = fork();
	if (process_id == SYS_ERROR)
		handle_error(SYS_ERROR, NULL);
	return (process_id);
}
