#include <env/env_utils.h>
#include <commands/quotes.h>
#include <commands/commands.h>
#include <defines.h>
#include <ctype.h>

int	get_key_len(const char *key)
{
	int	len;

	len = 0;
	while (key[len] != '\0' && !isspace(key[len])
		&& !is_quote(key[len]) && !is_variable(key[len]))
		++len;
	return (len);
}

t_bool	is_variable(char cur)
{
	return (cur == VARIABLE);
}
