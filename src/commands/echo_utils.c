#include "commands.h"
#include <ctype.h>
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>
#include <stdio.h>
#include <commands/echo_handle_quotes.h>

t_bool	is_valid_n_flag_extras(const char **input)
{
	char	cursor;
	int		counter;

	counter = 2;
	cursor = (*(*input + counter));
	while (cursor == 'n')
	{
		counter++;
		cursor = (*(*input + counter));
	}
	if (!isspace(cursor) && cursor != NULL_TERMINATOR)
		return (FALSE);
	*input += counter;
	return (TRUE);
}

t_bool	parse_n_flag(const char **input)
{
	skip_spaces(input);
	if (ft_strncmp((char *)*input, N_FLAG, ft_strlen(N_FLAG)) == 0)
	{
		if (!is_valid_n_flag_extras(input))
			return (FALSE);
		parse_n_flag(input);
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
		skip_spaces(input);
	}
}
