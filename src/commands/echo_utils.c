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

t_bool	parse_n_flag(t_arg *input)
{
	skip_spaces(&input->start);
	if (ft_strncmp(input->start, N_FLAG, ft_strlen(N_FLAG)) == 0)
	{
		if (!is_valid_n_flag_extras(&input->start))
			return (FALSE);
		parse_n_flag(input);
		return (TRUE);
	}
	return (FALSE);
}

void	write_to_stdout(const char *string_to_write)
{
	const int	len_inside = ft_strlen(string_to_write);

	write(STDOUT_FILENO, string_to_write, len_inside);
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