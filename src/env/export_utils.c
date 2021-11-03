#include <env/export_utils.h>
#include <env/env_utils.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <libft.h>
#include <stdio.h>
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

void	move_to_key_start(const char **kv_str)
{
	const char	*equalsign_position = get_equal_sign_position(*kv_str);
	int			space_index;
	char		*space_position;

	space_index = get_set_index((char *)*kv_str, WHITESSPACE);
	space_position = (char *)(*kv_str) + space_index;
	while (space_position && space_position < equalsign_position)
	{
		(*kv_str) += &space_position[0] - (*kv_str);
		skip_spaces(kv_str);
		space_index = get_set_index((char *)*kv_str, WHITESSPACE);
		space_position = (char *)(*kv_str) + space_index;
	}
	skip_spaces(kv_str);
}

t_bool	add_variable_to_tmp_env(t_env *tmp_env, \
										const char **key_value_str)
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
		(*key_value_str) += key_buffer.index + value_buffer.index + 1;
		return (TRUE);
	}
	else
		(*key_value_str) += key_buffer.index;
	return (FALSE);
}

int	add_variables_to_tmp_env(t_env *tmp_env, const char *key_value_str)
{
	int	variables_count;

	variables_count = 0;
	while (*key_value_str)
	{	
		move_to_key_start(&key_value_str);
		variables_count += \
		add_variable_to_tmp_env(&tmp_env[variables_count], &key_value_str);
		if (!get_equal_sign_position(key_value_str))
			break ;
	}
	return (variables_count);
}

t_bool	add_variables_to_env(t_env *env, \
									t_env *tmp_env, \
									int variables_count)
{
	t_bool	exit_code;
	int		i;

	i = 0;
	exit_code = TRUE;
	while (i < variables_count)
	{
		if (!is_valid_key(tmp_env[i].key, ft_strlen(tmp_env[i].key)))
		{
			printf("export: `%s=%s': not a valid identifier\n", tmp_env[i].key, tmp_env[i].value);
			exit_code = FALSE;
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
