#ifndef HANDLE_PIPES_H
# define HANDLE_PIPES_H

# define FIRST_PROCESS 0

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

int	handle_pipes(const t_command *commands[], int num_of_commands,
		const char *env[]);

#endif