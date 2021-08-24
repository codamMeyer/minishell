#include "pipe_utils.h"
#include "handle_pipes.h"
#include <unistd.h>
#include <stdio.h>
#include "../../libft/libft.h"
#include <sys/wait.h>

void	wait_for_all_processes(int *pid, int num_of_processes)
{
	int	i;

	i = 0;
	(void)num_of_processes;
	while (i < 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	handle_errors(int error_code, char *location)
{
	perror(location);
	exit(error_code);
}

int	execute_command(const char *path, char *argv[], const char *env[])
{
	return (execve(path, (char *const *)argv, (char *const *)env));
}

void	execute_commands(const t_command *command, const char *env[])
{
	char		**cmd;
	char		buffer[4096];

	if (1)
	{
		ft_strlcpy(&buffer[0], command->arg.start, command->arg_len + 1);
		cmd = ft_split(&buffer[0], SPACE);
		if (!cmd)
			handle_errors(3, "child, invalid command");
	}
	if (execute_command(command->exe_path, cmd, env) == SYS_ERROR)
		handle_errors(5, "child_process execute command");
}

int	create_new_process(t_multi_pipes *pipes)
{
	int	pid;

	if (pipe(pipes->current) == SYS_ERROR)
		handle_errors(7, "pipe current main");
	pid = fork();
	if (pid == SYS_ERROR)
		handle_errors(SYS_ERROR, "forking main");
	return (pid);
}
