#include <env/sort_env.h>
#include <env/environment.h>
#include <libft.h>
#include <stdio.h>

int	populate_env_index_buffer(int index_buffer[])
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
			index_buffer[j] = i;
			++j;
		}
		++i;
	}
	return (j);
}

int	sort_env(const t_env *env, int index_buffer[])
{
	const int	num_vars = populate_env_index_buffer(index_buffer);
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
			if (ft_strcmp(env[index_buffer[i]].key, \
				env[index_buffer[i + 1]].key) > 0)
			{
				tmp = index_buffer[i];
				index_buffer[i] = index_buffer[i + 1];
				index_buffer[i + 1] = tmp;
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
	int			index_buffer[ENV_SIZE];
	int			num_elements;
	int			i;

	num_elements = sort_env(env, index_buffer);
	i = 0;
	while (i < num_elements)
	{
		if (ft_strncmp(env[index_buffer[i]].key, "_", 2) != 0)
		{
			printf("declare -x ");
			printf("%s=", env[index_buffer[i]].key);
			printf("\"%s\"\n", env[index_buffer[i]].value);
		}
		++i;
	}
}
