#ifndef ERRORS_H
# define ERRORS_H
# include <errors/exit_code.h>
# define SHELL_NAME "BestShellEver: "

void		handle_error(t_exit_code code, \
						const char *location, \
						const char *filename);

#endif