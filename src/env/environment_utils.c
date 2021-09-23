#include <env/environment.h>
#include <libft.h>

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
	if (!env)
		return ;
	if (env->key)
		free(env->key);
	if (env->value)
		free(env->value);
	env->key = NULL;
	env->value = NULL;
}

t_env	*get_environment(void)
{
	static t_env	env[ENV_SIZE] = {};

	return (&env[0]);
}
