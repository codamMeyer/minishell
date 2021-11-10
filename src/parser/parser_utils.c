#include <string.h>
#include <libft.h>
#include <parser/parser.h>

void	skip_spaces(const char **input)
{
	while (*input && ft_isspace(*(*input)))
		++(*input);
}
