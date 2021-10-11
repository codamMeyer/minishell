#ifndef DISPATCHER_H
# define DISPATCHER_H
# include <commands/commands.h>
# include <defines.h>

typedef t_exit_code(*t_command_function)(t_command, t_output_stdout);

t_exit_code	unknown_command(t_command command, t_output_stdout output);
t_exit_code	dispatch_command(t_command *command, char *env[]);

#endif
