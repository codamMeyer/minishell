#include <env/environment.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

t_bool	export(t_env *env, const char *key_value_str)
{
	char	key_buffer[4096];
	char	value_buffer[4096];

	if (!copy_key_to_buffer(key_value_str, key_buffer) || \
		!copy_value_to_buffer(key_value_str, value_buffer))
		return (FALSE);
	if (change_value_of_existent_key(env, key_buffer, value_buffer))
		return (TRUE);
	return (set_new_key_value_pair(env, key_buffer, value_buffer));
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

void	display(t_env *env, t_output_stdout output)
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

t_env	*find(t_env *env, const char *key_name)
{
	const int	name_len = ft_strlen(key_name) + 1;
	int			i;

	if (!env)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strncmp(env[i].key, key_name, name_len) == 0)
			return (&env[i]);
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
