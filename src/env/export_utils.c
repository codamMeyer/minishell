#include <env/environment.h>
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

t_bool	copy_key_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	const int	key_len = delimiter_position - &key_value_str[0];

	if (!delimiter_position)
		return (FALSE);
	ft_bzero(buffer, 4096);
	ft_memcpy(&buffer[0], key_value_str, key_len);
	return (is_valid_key(&buffer[0], key_len));
}

t_bool	copy_value_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position =
		get_equal_sign_position(key_value_str) + 1;
	int			value_len;
	char		cur;

	value_len = 0;
	if (!delimiter_position)
		return (FALSE);
	cur = delimiter_position[value_len];
	while (cur && !isspace(cur))
	{
		++value_len;
		cur = delimiter_position[value_len];
	}
	ft_bzero(buffer, 4096);
	if (value_len != 0)
		ft_memcpy(&buffer[0], delimiter_position, value_len);
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
