#include <env/sort_env.h>
#include <env/environment.h>
#include <string.h>
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

int	sort_env(int buffer[])
{
	t_env	*env;
	int		j;
	int		i;
	int		tmp;
	int		max;

	i = 0;
	env = get_environment();
	max = populate_env_index_buffer(buffer);
	while (i < max)
	{
		j = 0;
		while (j < max - i - 1)
		{
			if (strcmp(env[buffer[j]].key, env[buffer[j + 1]].key) > 0)
			{
				tmp = buffer[j];
				buffer[j] = buffer[j + 1];
				buffer[j + 1] = tmp;
			}
			++j;
		}
		++i;
	}
	return (max);
}

void	display_sorted_env(void)
{
	int		buffer[ENV_SIZE];
	int		num_elements;
	int		i;
	t_env	*env;

	env = get_environment();
	num_elements = sort_env(buffer);
	i = 0;
	printf("\n");
	while (i < num_elements)
	{
		printf("--> %s=%s\n", env[buffer[i]].key, env[buffer[i]].value);
		++i;
	}
}
