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

static	int add_variables_to_tmp_env(t_env *tmp_env, const char *key_value_str)
{
	t_buffer	key_buffer;
	t_buffer	value_buffer;
	int			variables_count;

	variables_count = 0;
	while (*key_value_str)
	{
		init_buffer(&key_buffer);
		init_buffer(&value_buffer);
		int start = 0;
		skip_spaces(&key_value_str);
		while (key_value_str[start] && !isspace(key_value_str[start]) && key_value_str[start] != EQUAL_SIGN)
			++start;
		if (isspace(key_value_str[start]))
		{
			key_value_str += start;
			skip_spaces(&key_value_str);
		}
		if (copy_key_to_buffer(key_value_str, &key_buffer))
		{
			copy_value_to_buffer(key_value_str, &value_buffer);
			tmp_env[variables_count].key = ft_strdup(key_buffer.buf);
			tmp_env[variables_count].value = ft_strdup(value_buffer.buf);
			++variables_count;
			key_value_str += key_buffer.index + value_buffer.index + 1;
		}
		else
			key_value_str += key_buffer.index;
	}
	return (variables_count);
}

t_bool	export(t_env *env, const char *key_value_str)
{
	t_env		tmp_env[BUFFER_SIZE];
	t_exit_code	exit_code;
	int			i;
	int variables_count;

	if (!(*key_value_str))
	{
		display_sorted_env();
		return (0); // return exit code ?
	}
	exit_code = SUCCESS;
	variables_count = add_variables_to_tmp_env(&tmp_env[0], key_value_str);
	i = 0;
	while (i < variables_count)
	{
		if (!is_valid_key(tmp_env[i].key, ft_strlen(tmp_env[i].key)))
		{
			printf("invalid: %s=%s\n", tmp_env[i].key, tmp_env[i].value);
			exit_code &= FALSE;
		}
		else
		{
			set_key(env, tmp_env[i].key);
			set_value(env, tmp_env[i].key, tmp_env[i].value);
		}
		free(tmp_env[i].key);
		free(tmp_env[i].value);
		++i;
	}
	return (exit_code);
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
