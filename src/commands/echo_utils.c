#include "commands.h"
#include <libft.h>

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
	quotes->opening = FALSE;
	quotes->closing = FALSE;
	while (*input)
	{
		if (*input == INVERTED_COMMA && quotes->opening)
			quotes->closing = TRUE;
		else if (*input == INVERTED_COMMA)
			quotes->opening = TRUE;
		input++;
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
