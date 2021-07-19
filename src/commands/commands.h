#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>

void	exit_command(t_exit_code exit_code);

int		echo_command(const char **input);
char	*format_string(const char *input);
int		get_substr_len(const char *input);

#endif