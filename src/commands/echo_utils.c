#include "commands.h"
#include <ctype.h>
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>

t_quotes_position	get_quotes_positions(const char *input)
{
	t_quotes_position	quotes_position;

	if (*input == DOUBLE_QUOTES)
	{
		++input;
		quotes_position.start = input;
		quotes_position.end = ft_strchr(input, DOUBLE_QUOTES);
		return (quotes_position);
	}
	quotes_position.start = NULL;
	quotes_position.end = NULL;
	return (quotes_position);
}

t_bool	parse_n_flag(const char **input)
{
	while (isspace(*(*input)))
		++(*input);
	if (ft_strncmp((char *)*input, N_FLAG, ft_strlen(N_FLAG)) == 0)
	{
		advance_pointer(input, N_FLAG);
		return (TRUE);
	}
	return (FALSE);
}

void	echo_stdout(const char *string_to_write, int len)
{
	write(STDOUT_FILENO, string_to_write, len);
}

void	trim_extra_spaces_between_words(const char **input,
										char *stdout_buffer,
										int *buffer_index)
{
	if (isspace(*(*input)) && *(*input + 1))
	{
		stdout_buffer[*buffer_index] = SPACE;
		++(*buffer_index);
		while (isspace(*(*input)))
			++(*input);
	}
}

t_bool	is_double_quote(char c)
{
	return (c == DOUBLE_QUOTES);
}
