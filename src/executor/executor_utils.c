#include <stdio.h>
#include <libft.h>
#include <errno.h>
#include <sys/wait.h>
#include <string.h>
#include <commands/buffer.h>
#include <executor/executor_utils.h>
#include <executor/run_commands.h>
#include <env/env_for_exec.h>

/* exit_codes caused by signals are incremented with 128 */
t_exit_code	wait_for_all_processes(int num_of_processes, int *pids)
{
	const int	signal_increment = 128;
	int			i;
	t_exit_code	exit_code;
	int			status;

	i = 0;
	exit_code = 0;
	while (i < num_of_processes)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			exit_code = WTERMSIG(status) + signal_increment;
		i++;
	}
	return (exit_code);
}

static int	execute_command(const char *path, char *argv[])
{
	char	*updated_env[BUFFER_SIZE];

	env_to_char_pointer_array(updated_env);
	return (execve(path, (char *const *)argv, (char *const *)updated_env));
}

static	void	handle_execve_error(const char *cmd)
{
	const char	*no_file_or_dir = "No such file or directory";
	const char	*is_dir = "is a directory";

	if (errno == 2)
		write_execve_error(127, cmd, no_file_or_dir);
	else if (errno == 13
		&& (ft_strncmp(cmd, "./", 2) == SUCCESS || (cmd && cmd[0] == '/')))
		write_execve_error(126, cmd, is_dir);
	else
		handle_error(SYS_ERROR, NULL, cmd);
	exit(*get_exit_code());
}

void	execute_system_command(const t_command *command)
{
	char		**cmd;
	t_buffer	buffer;

	init_buffer(&buffer);
	while (command->arg.start < command->arg.end)
		append_expanded_input_to_buffer((t_arg *)&command->arg, &buffer);
	cmd = ft_split(&buffer.buf[0], SPACE_CHAR);
	if (!cmd)
		handle_error(MALLOC_ERROR, NULL, "malloc()");
	if (execute_command(command->exe_path, cmd) == SYS_ERROR)
	{
		handle_execve_error(*cmd);
		free((char *)command->exe_path);
	}
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
		handle_error(PIPE_ERROR, NULL, "pipe()");
	process_id = fork();
	if (process_id == SYS_ERROR)
		handle_error(FORK_ERROR, NULL, "fork()");
	return (process_id);
}
