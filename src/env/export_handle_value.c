#include <ctype.h>
#include <stdio.h>
#include <libft.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/command_table.h>

void	handle_quoted_value(const char *value, t_buffer *buffer)
{
	t_arg		arg;

	arg.start = value;
	parse_str_with_quotes(arg, buffer);
}

void	handle_unquoted_value(const char *value, t_buffer *buffer)
{
	t_arg	str;

	str.start = value;
	while (*str.start && !isspace(*str.start))
	{
		if (is_env_variable(str.start))
			append_env_value_to_buffer(&str, buffer);
		else
			append_char_to_buffer(&str, buffer);
	}
}

static int get_value_len(const char *value_string)
{
	int i = 0;
	while (value_string[i])
	{
		if (isspace(value_string[i]) \
		&& !is_between_quotes(value_string, i))
			return (i);
		++i;
	}
	return (i);
}

t_bool	copy_value_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str) + 1;
	char		cur;

	if (!delimiter_position)
		return (FALSE);
	cur = delimiter_position[0];
	if (is_quote(cur))
		handle_quoted_value(delimiter_position, buffer);
	else
		handle_unquoted_value(delimiter_position, buffer);
	buffer->index = get_value_len(delimiter_position);
	return (TRUE);
}

t_bool	set_value(t_env *env, char *key, char *value)
{
	t_env		*key_pair;

	key_pair = find_variable(env, key);
	free(key_pair->value);
	key_pair->value = ft_strdup(value);
	if (!key_pair->value)
	{
		free(key_pair->key);
		return (FALSE);
	}
	return (TRUE);
}
