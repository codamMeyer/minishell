#include <syntax/redirection_syntax.h>
#include <syntax/check_quotes_syntax.h>
#include <output/write_to_std.h>

/*
	for testing purposes this returns something.
	In the end it will call the error checking function
	that will also exit the current process
*/
t_bool	is_valid_syntax(const char *input)
{
	if (!is_valid_redirection_syntax(input))
		return (FALSE);
	else if (has_missing_quotes(input))
		return (FALSE);
	return (TRUE);
}
