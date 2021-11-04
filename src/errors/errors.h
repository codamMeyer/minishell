#ifndef ERRORS_H
# define ERRORS_H
# include <errors/exit_code.h>

void		handle_error(t_exit_code code, \
						const char *location, \
						const char *filename);

#endif