#include <libft.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/parser.h>

void	init_buffer(t_buffer *buffer)
{
	ft_bzero(&buffer->buf[0], BUFFER_SIZE);
	buffer->index = 0;
}

void	append_char_to_buffer(t_arg *arg, t_buffer *buffer)
{
	buffer->buf[buffer->index] = *arg->start;
	++(buffer->index);
	++(arg->start);
}

void	append_env_value_to_buffer(t_arg *arg, t_buffer *buffer, t_bool trimmed)
{
	t_env	*var;
	int		key_len;
	char	*value;

	++(arg->start);
	key_len = get_key_len(arg->start);
	var = find_variable(get_environment(), arg->start);
	if (var)
	{
		value = var->value;
		if (trimmed)
			skip_spaces((const char **)&value);
		while (*value)
		{
			if (buffer->buf[buffer->index] == SPACE_CHAR && trimmed)
				skip_spaces((const char **)&value);
			buffer->buf[buffer->index] = *value;
			++value;
			++(buffer->index);
		}
		if (trimmed && buffer->buf[buffer->index - 1] == SPACE_CHAR)
		{
			--(buffer->index);
			buffer->buf[buffer->index] = NULL_TERMINATOR;
		}
	}
	arg->start = arg->start + key_len;
}

void	append_quoted_string_to_buffer(t_arg *arg, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(arg->start);

	if (quotes.start && quotes.end)
	{
		arg->start = quotes.start;
		while (arg->start < quotes.end)
		{
			if (quotes.is_double_quote && is_env_variable(arg->start))
				append_env_value_to_buffer(arg, buffer, FALSE);
			else
				append_char_to_buffer(arg, buffer);
		}
		++arg->start;
	}
	else if (quotes.start)
		++arg->start;
}

void	append_expanded_input_to_buffer(t_arg *arg, t_buffer *buffer)
{
	if (is_quote(*arg->start))
		append_quoted_string_to_buffer(arg, buffer);
	else if (is_env_variable(arg->start))
		append_env_value_to_buffer(arg, buffer, TRUE);
	else
		append_char_to_buffer(arg, buffer);
}
