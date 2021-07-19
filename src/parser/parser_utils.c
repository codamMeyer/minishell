#include <parser/parser.h>
#include <ctype.h>
#include <string.h>

void	advance_pointer(const char **input, const char *parsed_str)
{
	*input += strlen(parsed_str);
}

void	skip_spaces(const char **input)
{
	while (isspace(*(*input)))
		++(*input);
}
