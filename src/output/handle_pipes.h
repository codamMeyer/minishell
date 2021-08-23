#ifndef HANDLE_PIPES_H
# define HANDLE_PIPES_H
# define FIRST_PROCESS 0
# define CHILD_PROCESS 0
# define SYS_ERROR -1
# define MAX_CMDS_PER_LINE 100

# include <commands/commands.h>
# include "redirection.h"

int		run_pipes(const char *env[]);
int		handle_pipes(t_command commands[],
			int num_of_commands, const char *env[]);
void	handle_errors(int error_code, char *location);

#endif