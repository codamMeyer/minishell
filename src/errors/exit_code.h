#ifndef EXIT_CODE_H
# define EXIT_CODE_H
# include <commands/buffer.h>
# define MALLOC_STR "malloc()"
# define DUP_STR "dup()"
# define DUP2_STR "dup2()"
# define PIPE_STR "pipe()"
# define FORK_STR "fork()"
# define CLOSE_STR "close()"

typedef enum e_exit_code
{
	FILE_ERROR = -2,
	SYS_ERROR = -1,
	SUCCESS = 0,
	ERROR = 1,
	MALLOC_ERROR = 2,
	DUP_ERROR = 3,
	FORK_ERROR = 4,
	PIPE_ERROR = 5,
	HOME_NOT_SET_ERROR = 6,
	EXIT_ARGS_ERROR = 7,
	EXECVE_ERROR = 8,
	IS_DIR_ERROR = 126,
	PERMISSION_ERROR = 126,
	UNKNOWN_COMMAND_ERROR = 127,
	NONEXISTANT_ERROR = 127,
	SYNTAX_ERROR = 258,
}	t_exit_code;

t_exit_code	*get_exit_code(void);
t_exit_code	set_exit_code(t_exit_code new_code);
void		append_exit_code_to_buffer(const char **start, t_buffer *buffer);
void		write_execve_error(t_exit_code code,
				const char *cmd, const char *error_msg);

#endif