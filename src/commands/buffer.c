#include <ctype.h>
#include <libft.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/parser.h>
#include <errors/exit_code.h>

static void	append_env_value_to_buffer(const char **start, \
									t_buffer *buffer, \
									t_bool should_trim)
{
	const t_env	*var = find_variable(get_environment(), *start);
	const int	key_len = get_key_len(*start);
	char		*value;

	if (var)
	{
		value = var->value;
		if (should_trim)
			skip_spaces((const char **)&value);
		while (*value)
		{
			if (buffer->index && ft_isspace(buffer->buf[buffer->index - 1]) \
				&& should_trim)
				skip_spaces((const char **)&value);
			if (*value)
				append_char_to_buffer((const char **)&value, buffer);
		}
		if (should_trim && ft_isspace(buffer->buf[buffer->index - 1]))
		{
			--(buffer->index);
			buffer->buf[buffer->index] = NULL_TERMINATOR;
		}
	}
	*start = *start + key_len;
}

static void	append_quoted_string_to_buffer(const char **start, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(*start);

	*start = quotes.start;
	while (*start < quotes.end)
	{
		if (quotes.is_double_quote && is_env_variable(*start))
		{
			++(*start);
			append_env_value_to_buffer(start, buffer, FALSE);
		}
		else
			append_char_to_buffer(start, buffer);
	}
	++(*start);
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

void	append_expanded_input_to_buffer(t_arg *arg, t_buffer *buffer)
{
	if (is_quote(*arg->start))
		append_quoted_string_to_buffer(&arg->start, buffer);
	else if (is_env_variable(arg->start))
	{
		++(arg->start);
		append_env_value_to_buffer(&arg->start, buffer, TRUE);
	}
	else if (*arg->start == '$' && is_quote(*(arg->start + 1)))
		++(arg->start);
	else if (ft_strncmp(arg->start, "$?", 2) == 0)
		append_exit_code_to_buffer(&arg->start, buffer);
	else if (ft_isspace(*arg->start))
		trim_extra_spaces(&arg->start, arg->end, buffer);
	else
		append_char_to_buffer(&arg->start, buffer);
}
