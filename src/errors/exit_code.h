#ifndef EXIT_CODE_H
# define EXIT_CODE_H
# include <commands/buffer.h>

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
	UNKNOWN_COMMAND_ERROR = 127,
	SYNTAX_ERROR = 258,
}	t_exit_code;

t_exit_code	*get_exit_code(void);
t_exit_code	set_exit_code(t_exit_code new_code);
void		append_exit_code_to_buffer(const char **start, t_buffer *buffer);

#endif