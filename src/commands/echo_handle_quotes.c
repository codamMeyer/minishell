#include <commands/echo_handle_quotes.h>
#include <defines.h>
#include <stdio.h>
#include <libft.h>

t_quotes_position	get_quotes_positions(const char *input)
{
	t_quotes_position	quotes_position;

	if (is_double_quote(*input))
	{
		++input;
		quotes_position.start = input;
		quotes_position.end = ft_strchr(input, DOUBLE_QUOTES);
		return (quotes_position);
	}
	quotes_position.start = NULL;
	quotes_position.end = NULL;
	return (quotes_position);
}

t_bool	is_double_quote(char c)
{
	return (c == DOUBLE_QUOTES);
}
