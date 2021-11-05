#include <string.h>
#include <libft.h>
#include <parser/parser.h>

void	advance_pointer(const char **input, const char *parsed_str)
{
	*input += strlen(parsed_str);
}

void	skip_spaces(const char **input)
{
	while (*input && ft_isspace(*(*input)))
		++(*input);
}

void	trim_extra_spaces(const char **start, const char *end, t_buffer *buffer)
{
	skip_spaces(start);
	if (*start < end)
	{
		--(*start);
		append_char_to_buffer(start, buffer);
	}
}
