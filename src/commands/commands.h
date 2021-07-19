#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>

typedef struct s_check_quotes
{
	t_bool opening;
	t_bool closing;
}	t_check_quotes;

void	exit_command(t_exit_code exit_code);

int		echo_command(const char **input);
char	*format_string(const char *input);
int		get_substr_len(const char *input);
t_bool	check_quotes(const char *input, t_check_quotes *quotes);

#endif