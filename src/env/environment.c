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

static t_bool	is_valid_key(char *key, int key_len)
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

static void	move_to_key_start(const char **kv_str)
{
	int start = 0;
	skip_spaces(kv_str);
	while ((*kv_str)[start] \
			&& !isspace((*kv_str)[start]) \
			&& (*kv_str)[start] != EQUAL_SIGN)
		++start;
	if (isspace((*kv_str)[start]))
	{
		(*kv_str) += start;
		skip_spaces(kv_str);
	}
}

static t_bool add_variable_to_tmp_env(t_env* tmp_env, const char** key_value_str)
{
	t_buffer	key_buffer;
	t_buffer	value_buffer;

	init_buffer(&key_buffer);
	init_buffer(&value_buffer);

	if (copy_key_to_buffer(*key_value_str, &key_buffer))
	{
		//TODO check if the line below returned true
		copy_value_to_buffer(*key_value_str, &value_buffer);
		tmp_env->key = ft_strdup(key_buffer.buf);
		tmp_env->value = ft_strdup(value_buffer.buf);
		(*key_value_str) += key_buffer.index + value_buffer.index + 1;
		return TRUE;
	}
	else
		(*key_value_str) += key_buffer.index;

	return FALSE;
}

static	int add_variables_to_tmp_env(t_env *tmp_env, const char *key_value_str)
{
	int			variables_count;

	variables_count = 0;
	while (*key_value_str)
	{	
		move_to_key_start(&key_value_str);
		variables_count += add_variable_to_tmp_env(&tmp_env[variables_count], &key_value_str);
	}
	return (variables_count);
}

static t_bool add_variables_to_env(t_env* env, t_env* tmp_env, int variables_count)
{
	t_bool	exit_code; // TODO SHOULD RETURN t_bool
	int i;

	exit_code = TRUE;
	i = 0;
	while (i < variables_count)
	{
		if (!is_valid_key(tmp_env[i].key, ft_strlen(tmp_env[i].key)))
		{
			printf("invalid: %s=%s\n", tmp_env[i].key, tmp_env[i].value);
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
	return exit_code;
}

t_bool	export(t_env *env, const char *key_value_str)
{
	t_env		tmp_env[BUFFER_SIZE];
	int variables_count;

	if (!(*key_value_str))
	{
		display_sorted_env();
		return (0); // return exit code ?
	}
	if (!get_equal_sign_position(key_value_str))
		return (0);
	variables_count = add_variables_to_tmp_env(&tmp_env[0], key_value_str);
	return (add_variables_to_env(env, tmp_env, variables_count));
}

void	unset(t_env *env, const char *key)
{
	t_arg		arg;
	t_buffer	key_buffer;
	t_env		*variable;

	arg.start = (char *)key;
	while (*arg.start)
	{
		init_buffer(&key_buffer);
		while (*arg.start && !isspace(*arg.start))
			append_expanded_input_to_buffer(&arg, &key_buffer);
		variable = find_variable(env, key_buffer.buf);
		free_key_value_pair(variable);
		skip_spaces(&arg.start);
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
