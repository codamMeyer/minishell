#ifndef REDIRECTION_H
# define REDIRECTION_H

typedef enum e_pipe_fds
{
	READ_FD = 0,
	WRITE_FD = 1,
	PIPE_BOTH_ENDS = 2,
}	t_pipe_fds;

typedef struct s_multi_pipes
{
	int	current[PIPE_BOTH_ENDS];
	int	previous[PIPE_BOTH_ENDS];
}	t_multi_pipes;

void	current_to_previous_pipe(t_multi_pipes *pipes);
void	redirect_in_and_output(t_multi_pipes *pipes,
			int process, int num_of_processes, t_files *files);

#endif