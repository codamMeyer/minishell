#include <ctype.h>
#include <libft.h>
#include <stdio.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <env/environment.h>
#include <env/env_utils.h>
#include <executor/run_commands.h>

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

t_bool	copy_key_to_buffer(const char *key_value_str, t_buffer *buffer)
{
	// should check if there is a space before the equal sign (outside quotes)
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	t_arg		arg;

	if (!delimiter_position)
		return (FALSE);
	arg.start = key_value_str;
	while (arg.start < delimiter_position)
		append_expanded_input_to_buffer(&arg, buffer);
	if (!is_valid_key(&buffer->buf[0], buffer->index))
		return (FALSE); // INVALID_IDENTIFIER 1
	buffer->index = delimiter_position - key_value_str;
	return (TRUE);
}

t_bool	set_key(t_env *env, char *key)
{
	const int	i = get_next_available_index(env);
	t_env		*is_set;

	is_set = find_variable(env, key);
	if (is_set)
		return (TRUE);
	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key);
		if (!env[i].key)
			handle_error(MALLOC_ERROR);
	}
	return (TRUE);
}
