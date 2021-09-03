#include <env/environment.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

t_bool	export(t_env *env, const char *key_value_str)
{
	char	key_buffer[4096];
	int		i;

	if (!copy_key_to_buffer(key_value_str, key_buffer))
		return (FALSE);
	i = get_next_available_index(env);
	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key_buffer);
		if (!env[i].key)
			return (FALSE);
		env[i].value = ft_strdup(get_equal_sign_position(key_value_str) + 1);
		if (!env[i].value)
		{
			free(env[i].key);
			return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}

void	unset(t_env *env, const char *key_name)
{
	const int	name_len = ft_strlen(key_name) + 1;
	int			i;

	if (!env)
		return ;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strncmp(env[i].key, key_name, name_len) == 0)
		{
			free_key_value_pair(&env[i]);
			break ;
		}
		++i;
	}
}

void	display(t_env *env)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key)
			printf("%s=%s\n", env[i].key, env[i].value);
		++i;
	}
}

char	*find( t_env *env, const char *key_name)
{
	const int	name_len = ft_strlen(key_name) + 1;
	int			i;

	if (!env)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strncmp(env[i].key, key_name, name_len) == 0)
			return (env[i].value);
		++i;
	}
	return (NULL);
}

void	destroy(t_env *env, int size)
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
