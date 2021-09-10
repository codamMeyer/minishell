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

void	set_stdout(int new_std_out);
void	set_stdin(int new_std_in);
// void	get_file_name(char *dst_buffer, const char *src);
void	previous_to_current_pipe(t_multi_pipes *pipes);
void	redirect_in_and_output(t_multi_pipes *pipes,
			int process, int num_of_processes, const char *cmd_string);

#endif