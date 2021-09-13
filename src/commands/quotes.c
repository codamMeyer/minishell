#include <commands/quotes.h>
#include <defines.h>
#include <stdio.h>
#include <libft.h>

t_quotes_position	get_quotes_positions(const char *input)
{
	t_quotes_position	quotes_position;

	quotes_position.is_double_quote = is_double_quote(*input);
	if (quotes_position.is_double_quote)
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

t_quotes_index	get_quotes_indexes(const char *input)
{
	char			*start;
	t_quotes_index	quotes;

	start = ft_strchr(input, DOUBLE_QUOTES);
	if (start)
	{
		quotes.start = start - &input[0];
		quotes.end = \
			ft_strchr(&input[quotes.start + 1], DOUBLE_QUOTES) - &input[0];
		return (quotes);
	}
	quotes.start = 0;
	quotes.end = 0;
	return (quotes);
}

t_bool	is_double_quote(char c)
{
	return (c == DOUBLE_QUOTES);
}

t_bool	is_single_quote(char c)
{
	return (c == SINGLE_QUOTES);
}
