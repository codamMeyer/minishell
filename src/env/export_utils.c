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

t_bool	handle_quoted_value(const char *value, char *buffer)
{
	t_arg		arg;
	t_buffer	tmp_buffer;
	
	arg.start = value;
	init_buffer(&tmp_buffer);
	parse_str_with_quotes(arg, &tmp_buffer);
	ft_bzero(buffer, 4096);
	if (!ft_memcpy(&buffer[0], &tmp_buffer.buf[0], tmp_buffer.index))
		return (FALSE);
	return (TRUE);
}

/*
	unquoted string should get value of env var
*/

t_bool	handle_unquoted_value(const char *value, char *buffer)
{
	int		i;
	int		buf_i;
	t_env	*env_var;

	i = 0;
	buf_i = 0;
	ft_bzero(buffer, BUFFER_SIZE);
	while (value[i] && !isspace(value[i]))
	{
		if (is_env_variable(&value[i]))
		{
			++i;
			env_var = find_variable(get_environment(), &value[i]);
			i += get_key_len(&value[i]);
			if (env_var)
			{
				ft_memcpy(&buffer[buf_i], env_var->value, ft_strlen(env_var->value));
				buf_i += ft_strlen(env_var->value);
			}
		}
		else
		{
			buffer[buf_i] = value[i];
			++i;
			++buf_i;
		}
	}
	return (TRUE);
}

t_bool	copy_value_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position =
		get_equal_sign_position(key_value_str) + 1;
	char		cur;

	if (!delimiter_position)
		return (FALSE);
	cur = delimiter_position[0];
	if (is_quote(cur))
		return (handle_quoted_value(delimiter_position, buffer));
	return (handle_unquoted_value(delimiter_position, buffer));
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
