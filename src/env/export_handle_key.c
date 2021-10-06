#include <ctype.h>
#include <libft.h>
#include <stdio.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <executor/run_commands.h>

static t_bool	is_valid_key(char *key, int key_len)
{
	int	i;

	i = 0;
	while (i < key_len)
	{
		if (!is_valid_key_char(key[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	copy_key_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	t_arg		str;

	if (!delimiter_position)
		return (FALSE);
	str.start = key_value_str;
	while (str.start < delimiter_position)
	{
		if (is_quote(*str.start))
			str = parse_str_with_quotes(str, buffer);
		if (is_env_variable(str.start))
			append_env_value_to_buffer(&str, buffer);
		else if (is_valid_key_char(*str.start))
			append_char_to_buffer(&str, buffer);
	}
	if (!is_valid_key(&buffer->buf[0], buffer->index))
		return (FALSE);
	buffer->index = delimiter_position - key_value_str;
	return (TRUE);
}

t_bool	set_key(t_env *env, char *key)
{
	const int	i = get_next_available_index(env);
	t_env		*is_set;

	is_set = find_variable(env, key);
	if (is_set)
		return (TRUE);
	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key);
		if (!env[i].key)
			return (FALSE);
	}
	return (TRUE);
}
