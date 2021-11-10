#include <ctype.h>
#include <stdio.h>
#include <libft.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/command_table.h>

t_bool	copy_value_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = \
		get_equal_sign_position(key_value_str) + 1;

	if (!delimiter_position)
		return (FALSE);
	ft_strlcpy(&buffer->buf[0], delimiter_position,
		ft_strlen(delimiter_position) + 1);
	buffer->index = ft_strlen(delimiter_position);
	return (TRUE);
}

void	set_kv_string(t_env *env, char *key, char *value)
{
	const int	key_len = ft_strlen(key);
	const int	value_len = ft_strlen(value);
	const int	len = key_len + value_len + 2;

	if (env->set)
		free(env->set);
	env->set = malloc(len);
	if (!env->set)
		return ;
	ft_strlcpy(env->set, key, key_len + 1);
	ft_strlcpy(&env->set[key_len], "=", 2);
	ft_strlcpy(&env->set[key_len + 1], value, value_len + 1);
}

void	set_value(t_env *env, char *key, char *value)
{
	t_env		*key_pair;

	key_pair = find_variable(env, key);
	free(key_pair->value);
	key_pair->value = ft_strdup(value);
	if (!key_pair->value)
	{
		free(key_pair->key);
		handle_error(MALLOC_ERROR, NULL, "malloc()");
	}
	set_kv_string(key_pair, key_pair->key, key_pair->value);
}
