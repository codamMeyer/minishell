#include <env/environment.h>

t_bool	env_to_char_pointer_array(char **our_env)
{
	const t_env	*env = get_environment();
	int			i;
	int			j;

	i = 0;
	j = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key)
		{
			our_env[j] = env[i].key;
			j++;
		}
		i++;
	}
	return (TRUE);
}
