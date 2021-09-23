#include <env/env_utils.h>
#include <commands/quotes.h>
#include <commands/commands.h>
#include <defines.h>
#include <ctype.h>
#include <stdio.h>

int	get_key_len(const char *key)
{
	int	len;

	len = 0;
	while (key[len] != '\0' && !isspace(key[len])
		&& !is_quote(key[len]) && key[len] != VARIABLE_TOKEN && key[len] != EQUAL_SIGN)
		++len;
	return (len);
}

t_bool	is_env_variable(const char *str)
{
	const char		next_char = str[1];
	const t_bool	is_valid_next_char = next_char && \
										!isspace(next_char) && \
										!is_quote(next_char);

	return (*str == VARIABLE_TOKEN && is_valid_next_char);
}
