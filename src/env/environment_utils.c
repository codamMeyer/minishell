#include <env/environment.h>
#include <libft.h>

t_bool	copy_key_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position = ft_strchr(key_value_str, '=');
	const int	key_len = delimiter_position - &key_value_str[0];

	if (!delimiter_position)
		return (FALSE);
	ft_bzero(buffer, 4096);
	ft_memccpy(&buffer[0], key_value_str, '=', key_len);
	return (TRUE);
}
