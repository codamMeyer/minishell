#include <libft.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>

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

void	append_env_value_to_buffer(t_arg *arg, t_buffer *buffer)
{
	t_env			*var;
	int				key_len;
	int				value_len;

	++(arg->start);
	value_len = 0;
	key_len = get_key_len(arg->start);
	var = find_variable(get_environment(), arg->start);
	if (var)
	{
		value_len = ft_strlen(var->value);
		ft_strlcpy(&buffer->buf[buffer->index], var->value, value_len + 1);
	}
	arg->start = arg->start + key_len;
	buffer->index += value_len;
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
				append_env_value_to_buffer(arg, buffer);
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
		append_env_value_to_buffer(arg, buffer);
	else
		append_char_to_buffer(arg, buffer);
}