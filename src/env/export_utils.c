#include <env/environment.h>
#include <ctype.h>
#include <libft.h>

t_bool	copy_key_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str);
	const int	key_len = delimiter_position - &key_value_str[0];

	if (!delimiter_position)
		return (FALSE);
	ft_bzero(buffer, 4096);
	ft_memcpy(&buffer[0], key_value_str, key_len);
	return (TRUE);
}

t_bool	copy_value_to_buffer(const char *key_value_str, char *buffer)
{
	const char	*delimiter_position = get_equal_sign_position(key_value_str) + 1;
	int         value_len;

    value_len = 0;
    if (!delimiter_position)
		return (FALSE);
    while (delimiter_position[value_len] && !isspace(delimiter_position[value_len]))
    {
        ++value_len;
    }
	ft_bzero(buffer, 4096);
	ft_memcpy(&buffer[0], delimiter_position, value_len);
	return (TRUE);
}
