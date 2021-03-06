#include <env/export_utils.h>
#include <env/env_utils.h>
#include <parser/command_table.h>
#include <output/write_to_std.h>
#include <libft.h>

t_bool	is_valid_key(char *key, int key_len)
{
	int	i;

	i = 0;
	if (ft_strlen(key) == 0)
		return (FALSE);
	if (ft_isdigit(key[i]))
		return (FALSE);
	while (i < key_len)
	{
		if (!is_valid_key_char(key[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	add_variable_to_tmp_env(t_env *tmp_env, char **key_value_str)
{
	t_buffer	key_buffer;
	t_buffer	value_buffer;

	init_buffer(&key_buffer);
	init_buffer(&value_buffer);
	if (copy_key_to_buffer(*key_value_str, &key_buffer))
	{
		copy_value_to_buffer(*key_value_str, &value_buffer);
		tmp_env->key = ft_strdup(key_buffer.buf);
		tmp_env->value = ft_strdup(value_buffer.buf);
		tmp_env->set = NULL;
		return (TRUE);
	}
	else
		(*key_value_str) += key_buffer.index;
	return (FALSE);
}

int	add_variables_to_tmp_env(t_env *tmp_env, char **arguments)
{
	int	variables_count;
	int	i;

	i = 1;
	variables_count = 0;
	while (arguments[i])
	{	
		variables_count += \
		add_variable_to_tmp_env(&tmp_env[variables_count], &arguments[i]);
		++i;
	}
	return (variables_count);
}

t_exit_code	add_variables_to_env(t_env *env, \
									t_env *tmp_env, \
									int variables_count)
{
	t_exit_code	exit_code;
	int			i;

	i = 0;
	exit_code = SUCCESS;
	while (i < variables_count)
	{
		if (!is_valid_key(tmp_env[i].key, ft_strlen(tmp_env[i].key)))
		{
			write_to_stderr("BestShellEver: export: `");
			write_to_stderr(tmp_env[i].key);
			write_to_stderr("=");
			write_to_stderr(tmp_env[i].value);
			write_to_stderr("': not a valid identifier\n");
			exit_code = ERROR;
		}
		else
		{
			set_key(env, tmp_env[i].key);
			set_value(env, tmp_env[i].key, tmp_env[i].value);
		}
		free_key_value_pair(&tmp_env[i]);
		++i;
	}
	return (exit_code);
}
