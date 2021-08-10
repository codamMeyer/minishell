#ifndef DISPATCHER_H
# define DISPATCHER_H
# include <defines.h>
# include <commands/commands.h>

void	unknown_command(const char **input, t_output_stdout output);
t_bool	dispatch_commands(const char **input, t_command command);

#endif