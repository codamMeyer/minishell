#ifndef REDIRECTION_H
# define REDIRECTION_H
# include <commands/commands.h>

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

typedef struct s_std_fd
{
	int	in;
	int	out;
}	t_std_fd;

void		restore_std_fds(t_std_fd fds);
t_std_fd	save_std_fds(void);
void		handle_stdin(int in_file, t_multi_pipes *pipes, int process);
void		handle_stdout(int out_file, t_multi_pipes *pipes, int process,
				int last_process);
void		set_stdout(int new_std_out);
void		set_stdin(int new_std_in);
void		previous_to_current_pipe(t_multi_pipes *pipes);
void		redirect_in_and_output(t_multi_pipes *pipes,
				int process, int num_of_processes, t_command *command);

#endif