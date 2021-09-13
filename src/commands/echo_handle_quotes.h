#ifndef ECHO_HANDLE_QUOTES_H
# define ECHO_HANDLE_QUOTES_H

# include <defines.h>

typedef struct s_quotes_position
{
	t_bool		is_double_quote;
	const char	*start;
	const char	*end;
}	t_quotes_position;

typedef struct s_quotes_index
{
	int	start;
	int	end;
}	t_quotes_index;

t_quotes_index		get_quotes_indexes(const char *input);
t_quotes_position	get_quotes_positions(const char *input);
t_bool				is_double_quote(char c);
t_bool				is_single_quote(char c);

#endif
