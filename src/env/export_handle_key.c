#include <libft.h>
#include <env/environment.h>
#include <env/env_utils.h>

t_bool	copy_key_to_buffer(char *key_value_str, t_buffer *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	int			key_len;

	if (!delimiter_position)
		return (FALSE);
	if (delimiter_position == key_value_str)
		return (TRUE);
	key_len = delimiter_position - key_value_str;
	ft_strlcpy(&buffer->buf[0], key_value_str, key_len + 1);
	buffer->index = key_len;
	return (TRUE);
}

void	set_key(t_env *env, char *key)
{
	const int	i = get_next_available_index(env);
	t_env		*is_set;

	is_set = find_variable(env, key);
	if (is_set)
		return ;
	if (i < ENV_SIZE)
	{
		env[i].key = ft_strdup(key);
		if (!env[i].key)
			handle_error(MALLOC_ERROR, NULL, "malloc()");
	}
}
