#include <commands/quotes.h>
#include <env/env_utils.h>
#include <env/environment.h>
#include <libft.h>
#include <ctype.h>

t_arg	parse_str_with_quotes(t_arg arg, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(arg.start);

	if (quotes.start && quotes.end)
	{
		arg.start = quotes.start;
		while (arg.start < quotes.end)
		{
			if (quotes.is_double_quote && is_env_variable(arg.start))
				append_env_value_to_buffer(&arg, buffer);
			else
				arg = append_char_to_buffer(arg, buffer);
		}
		++arg.start;
	}
	else if (quotes.start)
		++arg.start;
	return (arg);
}
