#include <ctype.h>
#include <libft.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/parser.h>
#include <errors/exit_code.h>

void	append_env_value_to_buffer(const char **start, t_buffer *buffer)
{
	const t_env	*var = find_variable(get_environment(), *start);
	const int	key_len = get_key_len(*start);

	if (var)
	{
		ft_strlcpy(&buffer->buf[buffer->index],
			var->value, ft_strlen(var->value) + 1);
		buffer->index += ft_strlen(var->value);
	}
	*start = *start + key_len;
}

void	append_quoted_string_to_buffer(const char **start, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(*start);

	*start = quotes.start - 1;
	while (*start <= quotes.end)
	{
		if (quotes.is_double_quote && (is_env_variable(*start)))
		{
			++(*start);
			append_env_value_to_buffer(start, buffer);
		}
		else
			append_char_to_buffer(start, buffer);
	}
}

void	init_buffer(t_buffer *buffer)
{
	ft_bzero(&buffer->buf[0], BUFFER_SIZE);
	buffer->index = 0;
}

void	append_char_to_buffer(const char **start, t_buffer *buffer)
{
	buffer->buf[buffer->index] = **start;
	++(buffer->index);
	++(*start);
}
