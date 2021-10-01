#include <libft.h>
#include <commands/quotes.h>

t_quotes_position	get_quotes_positions(const char *input)
{
	t_quotes_position	quotes_position;
	char				closing_quote;

	if (!is_quote(*input))
	{
		quotes_position.start = NULL;
		quotes_position.end = NULL;
		return (quotes_position);
	}
	quotes_position.is_double_quote = is_double_quote(*input);
	closing_quote = *input;
	++input;
	quotes_position.start = input;
	quotes_position.end = ft_strchr(input, closing_quote);
	return (quotes_position);
}

t_quotes_index	get_quotes_indexes(const char *input)
{
	char				*start;
	t_quotes_position	pos_quotes;
	t_quotes_index		quotes;

	start = (char *)input;
	while (*start && !is_quote(*start))
		++start;
	pos_quotes = get_quotes_positions(start);
	if (!pos_quotes.start || !pos_quotes.end)
	{
		quotes.start = 0;
		quotes.end = 0;
		return (quotes);
	}
	quotes.start = pos_quotes.start - &input[0] - 1;
	quotes.end = pos_quotes.end - &input[0];
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

t_bool	is_quote(char c)
{
	return (is_single_quote(c) || is_double_quote(c));
}
