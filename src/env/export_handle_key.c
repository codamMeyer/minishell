#include <env/environment.h>
#include <env/env_utils.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <ctype.h>
#include <libft.h>
#include <stdio.h>

static t_bool	is_valid_key(char *key, int key_len)
{
	int	i;

	i = 0;
	while (i < key_len)
	{
		if (isspace(key[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	copy_key_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	const int	key_len = delimiter_position - &key_value_str[0];
	t_arg		str;
	t_buffer	tmp_buffer;

	init_buffer(&tmp_buffer);
	if (!delimiter_position)
		return (FALSE);
	ft_memcpy(&tmp_buffer.buf[0], key_value_str, key_len);
	str.start = &tmp_buffer.buf[0];
	while (*str.start && !isspace(*str.start))
	{
		if (is_env_variable(str.start))
			append_env_value_to_buffer(&str, buffer);
		else
			append_char_to_buffer(&str, buffer);
	}
	return (is_valid_key(&buffer->buf[0], key_len));
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
