#ifndef ERRORS_H
#define ERRORS_H
#include <defines.h>

t_exit_code	*get_return_code(void);
t_exit_code set_return_code(t_exit_code new_code);

#endif