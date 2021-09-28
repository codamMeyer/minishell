#include <ctype.h>
#include <libft.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>


t_bool	handle_quoted_value(const char *value, t_buffer *buffer)
{
	t_arg		arg;

	arg.start = value;
	parse_str_with_quotes(arg, buffer);
	return (TRUE);
}

t_bool	handle_unquoted_value(const char *value, t_buffer *buffer)
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
	return (TRUE);
}

t_bool	copy_value_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position =
		get_equal_sign_position(key_value_str) + 1;
	char		cur;

	if (!delimiter_position)
		return (FALSE);
	cur = delimiter_position[0];
	if (is_quote(cur))
	{
		handle_quoted_value(delimiter_position, buffer);
		buffer->index += 2;
		return (TRUE);
	}
	return (handle_unquoted_value(delimiter_position, buffer));
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
