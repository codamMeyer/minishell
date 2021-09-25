#include <defines.h>
#include <commands/commands.h>

t_bool	is_valid_angled_brackets_syntax(const char *input)
{
	(void)input;
	return (TRUE);
}

t_bool	is_valid_pipes_syntax(const char *input)
{
	if (*input == PIPE)
		return (FALSE);
	return (TRUE);
}

t_bool	is_valid_syntax(const char *input)
{
	if (!is_valid_pipes_syntax(input))
		return (FALSE);
	else if (!is_valid_angled_brackets_syntax(input))
		return (FALSE);
	return (TRUE);
}
