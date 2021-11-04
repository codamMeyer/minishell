#include <ctype.h>
#include <stdio.h>
#include <libft.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <parser/command_table.h>

static int	get_value_len(const char *value_string)
{
	int	i;

	i = 0;
	while (value_string[i])
	{
		if (ft_isspace(value_string[i]) \
		&& !is_between_quotes(value_string, i))
			return (i);
		++i;
	}
	return (i);
}

t_bool	copy_value_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = \
		get_equal_sign_position(key_value_str) + 1;
	t_arg		arg;

	if (!delimiter_position)
		return (FALSE);
	arg.start = &delimiter_position[0];
	while (*arg.start && !ft_isspace(*arg.start))
		append_expanded_input_to_buffer(&arg, buffer);
	buffer->index = get_value_len(delimiter_position);
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
