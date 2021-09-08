#ifndef DISPATCHER_H
# define DISPATCHER_H
# include <defines.h>
# include <commands/commands.h>

typedef t_exit_code(*t_command_function)(t_command, t_output_stdout);

t_exit_code	unknown_command(t_command command, t_output_stdout output);
t_exit_code	dispatch_commands(const t_command *command_table, int num_commands);

#endif
