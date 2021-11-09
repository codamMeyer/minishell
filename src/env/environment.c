#include <ctype.h>
#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <commands/buffer.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <env/sort_env.h>
#include <parser/parser.h>
#include <env/export_utils.h>

t_exit_code	export(t_env *env, char **arguments)
{
	t_env	tmp_env[BUFFER_SIZE];
	int		variables_count;

	variables_count = add_variables_to_tmp_env(tmp_env, arguments);
	return (add_variables_to_env(env, tmp_env, variables_count));
}

void	unset(t_env *env, char **arguments)
{
	t_env	*variable;
	int		i;

	i = 1;
	while (arguments[i])
	{
		variable = find_variable(env, arguments[i]);
		free_key_value_pair(variable);
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
			output(env[i].set);
			output("\n");
		}
		++i;
	}
}

t_env	*find_variable(t_env *env, const char *key)
{
	const size_t	key_len = get_key_len(key);
	int				i;

	if (!env || !key_len)
		return (NULL);
	i = 0;
	while (i < ENV_SIZE)
	{
		if (env[i].key && ft_strlen(env[i].key) == key_len
			&& ft_strncmp(env[i].key, key, key_len) == 0)
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
