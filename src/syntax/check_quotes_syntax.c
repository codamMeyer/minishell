#include <syntax/check_quotes_syntax.h>
#include <commands/quotes.h>
#include <parser/command_table.h>
#include <stdio.h>

static char	*find_quote(const char *input)
{
	while (*input)
	{
		if (is_quote(*input))
			return ((char *)input);
		++input;
	}
	return ((char *)input);
}

t_exit_code	has_missing_quotes(const char *input, t_output_stdout output)
{
	t_quotes_position	quotes;

	quotes.start = find_quote(input);
	if (!*quotes.start)
		return (SUCCESS);
	quotes = get_quotes_positions(quotes.start);
	while (quotes.start && quotes.end)
	{
		++quotes.end;
		quotes.end = find_quote(quotes.end);
		quotes = get_quotes_positions(quotes.end);
	}
	if (quotes.start)
	{
		handle_error(SYNTAX_ERROR, NULL, NULL);
		output("Missing closing quote\n");
		return (ERROR);
	}
	return (SUCCESS);
}
