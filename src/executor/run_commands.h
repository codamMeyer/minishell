#ifndef RUN_COMMANDS_H
# define RUN_COMMANDS_H
# define FIRST_PROCESS 0
# define CHILD_PROCESS 0
# define SYS_ERROR -1
# include <commands/commands.h>
# include <executor/redirection.h>

t_exit_code	run_commands(t_command commands[],
			int num_of_commands, char *env[]);

#endif
