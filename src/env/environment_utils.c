#include <env/environment.h>
#include <libft.h>

t_bool	copy_key_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	const int	key_len = delimiter_position - &key_value_str[0];

	if (!delimiter_position)
		return (FALSE);
	ft_bzero(buffer, 4096);
	ft_memcpy(&buffer[0], key_value_str, key_len);
	return (TRUE);
}

int	get_next_available_index(t_env *env)
{
	int	i;

	i = 0;
	while (i < ENV_SIZE && env[i].key)
		++i;
	return (i);
}

char	*get_equal_sign_position(const char *key_value_str)
{
	return (ft_strchr(key_value_str, EQUAL_SIGN));
}

void	free_key_value_pair(t_env *env)
{
	free(env->key);
	free(env->value);
	env->key = NULL;
	env->value = NULL;
}
