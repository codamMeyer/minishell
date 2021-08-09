#ifndef ECHO_HANDLE_QUOTES_H
# define ECHO_HANDLE_QUOTES_H

# include <defines.h>

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

typedef struct s_quotes_position
{
	const char	*start;
	const char	*end;
}	t_quotes_position;

t_quotes_position	get_quotes_positions(const char *input);
t_bool				is_double_quote(char c);

#endif