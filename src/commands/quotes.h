#ifndef QUOTES_H
# define QUOTES_H
# include <commands/commands.h>
# include <commands/buffer.h>
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
t_bool				is_quote(char c);

#endif
