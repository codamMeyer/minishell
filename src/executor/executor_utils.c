#include <stdio.h>
#include <libft.h>
#include <sys/wait.h>
#include <executor/executor_utils.h>
#include <executor/run_commands.h>

void	wait_for_all_processes(int num_of_processes)
{
	int	i;

	i = 0;
	while (i < num_of_processes)
	{
		waitpid(DEFAULT_WAIT_ID, NULL, 0);
		i++;
	}
}

/*
	Basic error handeling fucntion to make troubleshooting easier for system calls
*/
void	handle_errors(int error_code, char *description_location)
{
	perror(description_location);
	exit(error_code);
}

/*
	Done like this to not have confusing typecasting flying around
*/
int	execute_command(const char *path, char *argv[], char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

void	execute_system_command(const t_command *command, char *env[])
{
	char		**cmd;
	char		buffer[4096];

	ft_strlcpy(&buffer[0], command->arg.start, command->arg.len + 1);
	cmd = ft_split(&buffer[0], SPACE_CHAR);
	if (!cmd)
		handle_errors(3, "child, invalid command");
	if (execute_command(command->exe_path, cmd, env) == SYS_ERROR)
		handle_errors(5, "child_process execute command");
}

/*
	Calls pipe() first so that the pipe fds are accesible in
	the main as well as in the child process
*/
int	create_new_process(t_multi_pipes *pipes)
{
	int	process_id;

	if (pipe(pipes->current) == SYS_ERROR)
		handle_errors(7, "pipe current main");
	process_id = fork();
	if (process_id == SYS_ERROR)
		handle_errors(SYS_ERROR, "forking main");
	return (process_id);
}
