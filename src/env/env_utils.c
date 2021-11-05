#include <ctype.h>
#include <libft.h>
#include <commands/quotes.h>
#include <commands/commands.h>
#include <env/env_utils.h>
#include <stdio.h>

t_bool	is_valid_key_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	get_key_len(const char *key)
{
	int	len;

	len = 0;
	while (is_valid_key_char(key[len]))
		++len;
	return (len);
}

t_bool	is_env_variable(const char *str)
{
	const char		next_char = str[1];
	const t_bool	is_valid_next_char = is_valid_key_char(next_char);

	return (*str == VARIABLE_TOKEN && is_valid_next_char);
}
