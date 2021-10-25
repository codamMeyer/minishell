#include <env/sort_env.h>
#include <env/environment.h>
#include <string.h>
#include <libft.h>
#include <stdio.h>

int	populate_env_index_buffer(int buffer[])
{
	t_env	*env;
	int		i;
	int		j;

	env = get_environment();
	i = 0;
	j = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key)
		{
			buffer[j] = i;
			++j;
		}
		++i;
	}
	return (j);
}

int	sort_env(const t_env *env, int buffer[])
{
	const int	num_vars = populate_env_index_buffer(buffer);
	t_bool		swapped;
	int			tmp;
	int			i;

	swapped = TRUE;
	while (swapped)
	{
		i = 0;
		swapped = FALSE;
		while (i < num_vars - 1)
		{
			if (ft_strcmp(env[buffer[i]].key, env[buffer[i + 1]].key) > 0)
			{
				tmp = buffer[i];
				buffer[i] = buffer[i + 1];
				buffer[i + 1] = tmp;
				swapped = TRUE;
			}
			++i;
		}
	}
	return (num_vars);
}

void	display_sorted_env(void)
{
	const t_env	*env = get_environment();
	int			buffer[ENV_SIZE];
	int			num_elements;
	int			i;

	num_elements = sort_env(env, buffer);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(env[buffer[i]].key, "_", 2) != 0)
		{
			printf("declare -x ");
			printf("%s=\"%s\"\n", env[buffer[i]].key, env[buffer[i]].value);
		}
		++i;
	}
}
