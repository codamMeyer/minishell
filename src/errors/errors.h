#ifndef ERRORS_H
#define ERRORS_H

typedef enum e_exit_code
{
	FILE_ERROR = -2,
	SYS_ERROR = -1,
	SUCCESS = 0,
	ERROR = 1,
	MALLOC_ERROR = 2,
	HOME_NOT_SET_ERROR = 3,
	UNKNOWN_COMMAND_ERROR = 127,
}	t_exit_code;

t_exit_code	*get_return_code(void);
t_exit_code set_return_code(t_exit_code new_code);
void        handle_error(t_exit_code code, const char *location, const char *filename);


#endif