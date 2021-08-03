#include "commands.h"
#include <ctype.h>
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>

int	get_substr_len(const char *input)
{
	const int	strlen = ft_strlen(input);
	int			i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
			return (i);
		i++;
	}
	if (i == strlen)
		return (strlen);
	return (0);
}

t_bool	has_inverted_comma_set(const char *input, t_check_quotes *quotes)
{
	char cur;

	quotes->opening = FALSE;
	quotes->closing = FALSE;
	cur = *input;
	while (cur)
	{
		if (cur == INVERTED_COMMA && quotes->opening)
			quotes->closing = TRUE;
		else if (cur == INVERTED_COMMA)
			quotes->opening = TRUE;
		input++;
		cur = *input;
	}
	if (quotes->opening && quotes->closing)
		return (TRUE);
	return (FALSE);
}

char	**format_string_with_quotes(const char *str_w_quotes)
{
	char		**split_strings;
	const char	*clean_str = ft_strtrim(str_w_quotes, WHITESSPACE_AND_QUOTES);

	split_strings = ft_split(clean_str, NULL_TERMINATOR);
	free((char *)clean_str);
	return (split_strings);
}

void	write_space_between_words(const char *next_string)
{
	if (next_string)
		write(STDOUT_FILENO, " ", 1);
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
