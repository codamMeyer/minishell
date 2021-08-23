#include <env/environment.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft.h>

t_bool	export_env(char *key_value_str, t_env *env)
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

void	unset_env(char *key_name, t_env *env)
{
	const int	name_len_including_null = ft_strlen(key_name) + 1;
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && \
		ft_strncmp(env[i].key, key_name, name_len_including_null) == 0)
		{
			free(env[i].key);
			free(env[i].value);
			env[i].key = NULL;
			env[i].value = NULL;
			break ;
		}
		++i;
	}
}

void	display_env(t_env *env)
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

char	*find_in_env(char *key_name, t_env *env)
{
	const int	name_len_including_null = ft_strlen(key_name) + 1;
	int	i;

	if (!env)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && \
		ft_strncmp(env[i].key, key_name, name_len_including_null) == 0)
			return (env[i].value);
		++i;
	}
	return (NULL);
}

void	destroy_env(t_env env[], int size)
{
	int	i;

	if (!env)
		return ;
	i = 0;
	while (i < size)
	{
		free(env[i].key);
		free(env[i].value);
		env[i].key = NULL;
		env[i].value = NULL;
		++i;
	}
}
