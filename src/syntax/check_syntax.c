#include <syntax/redirection_syntax.h>
#include <syntax/check_quotes_syntax.h>
#include <output/write_to_std.h>

t_bool	is_valid_syntax(const char *input)
{
	if (!is_valid_redirection_syntax(input))
		return (FALSE);
	else if (has_missing_quotes(input))
		return (FALSE);
	return (TRUE);
}
