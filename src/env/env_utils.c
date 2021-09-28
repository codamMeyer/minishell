#include <ctype.h>
#include <commands/quotes.h>
#include <commands/commands.h>
#include <env/env_utils.h>

static t_bool	is_valid_key_char(char c)
{
	return (c != NULL_TERMINATOR
		&& !isspace(c)
		&& !is_quote(c)
		&& c != VARIABLE_TOKEN
		&& c != EQUAL_SIGN);
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
