#include <env/environment.h>
#include <commands/echo_utils.h>
#include <commands/echo_handle_quotes.h>
#include <ctype.h>
#include <libft.h>

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
	if (value_len == 0)
		return (TRUE);
	ft_memcpy(&buffer[0], delimiter_position, value_len);
	return (TRUE);
}

t_bool	change_value_of_existent_key(t_env *env, char *key, char *value)
{
	t_env	*is_set;

	is_set = find(env, key);
	if (is_set)
	{
		free(is_set->value);
		is_set->value = ft_strdup(value);
		if (!is_set->value)
		{
			free(is_set->key);
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

t_bool	set_new_key_value_pair(t_env *env, char *key, char *value)
{
	const int	i = get_next_available_index(env);

	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key);
		if (!env[i].key)
			return (FALSE);
		env[i].value = ft_strdup(value);
		if (!env[i].value)
		{
			free(env[i].key);
			env[i].key = NULL;
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}
