#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>

# define WHITESSPACE_AND_QUOTES " 	\""

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

void	exit_command(t_exit_code exit_code);

int		echo_command(const char **input);
char	**parse_echo(const char **input);
int		get_substr_len(const char *input);
t_bool	check_quotes(const char *input, t_check_quotes *quotes);
char	**format_string_with_quotes(const char *str_w_quotes);

#endif
