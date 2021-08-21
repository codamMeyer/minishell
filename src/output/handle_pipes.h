#ifndef HANDLE_PIPES_H
# define HANDLE_PIPES_H

# define FIRST_PROCESS 0
# define CHILD_PROCESS 0
# define MAX_CMDS_PER_LINE 100

typedef struct s_arg
{
	const char	*start;
	const char	*end;
}	t_arg;

typedef struct s_fds
{
	int	in_fd;
	int out_fd;
	int	err_fd;
}	t_fds;

typedef struct s_command
{
	t_arg			arg;
	int				arg_len;
	const char		*exe_path;
}	t_command;

typedef enum e_pipe_fds
{
	READ_FD = 0,
	WRITE_FD = 1,
	PIPE_BOTH_ENDS = 2
}	t_pipe_fds;

typedef struct s_multi_pipes
{
	int	current[PIPE_BOTH_ENDS];
	int	previous[PIPE_BOTH_ENDS];
}	t_multi_pipes;

int	handle_pipes(t_command commands[],
		int num_of_commands, const char *env[]);

#endif