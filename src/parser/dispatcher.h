#ifndef DISPATCHER_H
# define DISPATCHER_H
# include <defines.h>
# include <commands/commands.h>

t_bool	unknown_command(const char **input, t_output_stdout output);
t_bool	dispatch_commands(const char **input, const t_command *command_table, int num_commands);

#endif