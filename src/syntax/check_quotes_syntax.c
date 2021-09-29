#include <syntax/check_quotes_syntax.h>
#include <commands/quotes.h>

t_exit_code	is_missing_quotes(const char *input, t_output_stdout output)
{
	t_quotes_position	quotes;

	while (*input && !is_quote(*input))
		++input;
	if (!*input)
		return (SUCCESS);
	quotes = get_quotes_positions(input);
	while (quotes.start && quotes.end)
	{
		++quotes.end;
		while (*quotes.end && !is_quote(*quotes.end))
			++quotes.end;
		quotes = get_quotes_positions(quotes.end);
	}
	if (quotes.start)
	{
		output("Missing closing quote\n");
		return (ERROR);
	}
	return (SUCCESS);
}
