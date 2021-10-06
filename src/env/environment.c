#include <ctype.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/parser.h>

t_bool	export(t_env *env, const char *key_value_str)
{
	t_buffer	key_buffer;
	t_buffer	value_buffer;

	while (*key_value_str)
	{
		init_buffer(&key_buffer);
		init_buffer(&value_buffer);
		if (!copy_key_to_buffer(key_value_str, &key_buffer) || \
			!copy_value_to_buffer(key_value_str, &value_buffer))
			return (FALSE);
		if (!set_key(env, &key_buffer.buf[0])
			|| !set_value(env, &key_buffer.buf[0], &value_buffer.buf[0]))
			return (FALSE);
		key_value_str += key_buffer.index + value_buffer.index + 1;
		skip_spaces(&key_value_str);
	}
	return (TRUE);
}

t_arg	copy_key_to_buffer_and_unset(t_env *env, t_arg str, t_buffer *buffer)
{
	t_env *variable;
	
	while (*str.start && !isspace(*str.start))
	{
		if (is_quote(*str.start))
			parse_str_with_quotes(str, buffer);
		if (is_env_variable(str.start))
			append_env_value_to_buffer(&str, buffer);
		else
			append_char_to_buffer(&str, buffer);
	}
	variable = find_variable(env, buffer->buf);
	free_key_value_pair(variable);
	return (str);
}

void	unset(t_env *env, const char *key)
{
	t_arg		str;
	t_buffer	key_buffer;

	str.start = (char *)key;
	while (*str.start)
	{
		init_buffer(&key_buffer);
		str = copy_key_to_buffer_and_unset(env, str, &key_buffer);
		skip_spaces(&str.start);
	}
}

void	display_env(t_env *env, t_output_stdout output)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key)
		{
			output(env[i].key);
			output("=");
			output(env[i].value);
			output("\n");
		}
		++i;
	}
}

t_env	*find_variable(t_env *env, const char *key)
{
	const size_t	key_len = get_key_len(key);
	int				i;

	if (!env || !key_len)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strlen(env[i].key) == key_len
			&& ft_strncmp(env[i].key, key, key_len) == 0)
			return (&env[i]);
		++i;
	}
	return (NULL);
}

void	destroy_env(t_env *env, int size)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < size)
	{
		free_key_value_pair(&env[i]);
		++i;
	}
}
