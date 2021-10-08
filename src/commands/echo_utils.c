#include <ctype.h>
#include <libft.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <parser/parser.h>

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
