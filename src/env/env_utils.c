#include <env/env_utils.h>
#include <commands/quotes.h>
#include <commands/commands.h>
#include <defines.h>
#include <ctype.h>
#include <stdio.h>

t_bool	is_invalid_key_char(char c)
{
	return (c == '\0'
		|| isspace(c)
		|| is_quote(c)
		|| c == VARIABLE_TOKEN
		|| c == EQUAL_SIGN);
}

int	get_key_len(const char *key)
{
	int	len;

	len = 0;
	while (!is_invalid_key_char(key[len]))
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
