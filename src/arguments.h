#ifndef ARGUMENTS_H
# define ARGUMENTS_H
# include <commands/commands.h>

char	**split_command_args(t_arg arg);
void	destroy_split_arg(char **args);

#endif