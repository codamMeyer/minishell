#include <env/environment.h>
#include <env/env_utils.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>
#include <ctype.h>

t_bool	export(t_env *env, const char *key_value_str)
{
	char	key_buffer[4096];
	char	value_buffer[4096];

	if (!copy_key_to_buffer(key_value_str, key_buffer) || \
		!copy_value_to_buffer(key_value_str, value_buffer))
		return (FALSE);
	if (!set_key(env, key_buffer))
		return (FALSE);
	return (set_value(env, key_buffer, value_buffer));
}

void	unset(t_env *env, const char *key)
{
	int	name_len;
	int	i;

	if (!env)
		return ;
	i = 0;
	name_len = 0;
	while (!isspace(key[name_len]))
		++name_len;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strncmp(env[i].key, key, name_len) == 0)
		{
			free_key_value_pair(&env[i]);
			break ;
		}
		++i;
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
	const size_t	name_len = get_key_len(key);
	int			i;

	if (!env || !name_len)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strlen(env[i].key) == name_len && ft_strncmp(env[i].key, key, name_len) == 0)
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
