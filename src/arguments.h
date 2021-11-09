#ifndef ARGUMENTS_H
# define ARGUMENTS_H
# include <commands/commands.h>

void    populate_buffer_with_expanded_value(t_arg *arg, t_buffer *buffer);
char	**split_command_args(t_arg arg);
void	destroy_split_arg(char **args);

#endif