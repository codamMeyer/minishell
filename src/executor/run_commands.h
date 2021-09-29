#ifndef RUN_COMMANDS_H
# define RUN_COMMANDS_H
# define FIRST_PROCESS 0
# define CHILD_PROCESS 0
# define SYS_ERROR -1
# define MAX_CMDS_PER_LINE 100

# include <commands/commands.h>
# include "redirection.h"

int		run_pipes(const char *env[]);
int		run_commands(t_command commands[],
			int num_of_commands, char *env[]);
void	create_table(t_command commands[], char *arg, char *path);

#endif