#include <env/environment.h>
#include <stdlib.h>
#include <libft.h>

t_bool	export_env_set(char *key_value_str, t_env *env)
{
	const char	*delimiter_position = ft_strchr(key_value_str, '=');
	const int	key_len = delimiter_position - &key_value_str[0];
	char		key_buffer[4096];
	int			i;

	ft_memccpy(&key_buffer[0], key_value_str, '=', key_len);
	i = 0;
	while (i < ENV_SIZE && env[i].key)
		++i;
	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key_buffer);
		env[i].value = ft_strdup(ft_strchr(key_value_str, '=') + 1);
		if (env[i].key && env[i].value)
			return (TRUE);
	}
	return (FALSE);
}

void	destro_env_set(t_env *env)
{
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	env->key = NULL;
	env->value = NULL;
}
