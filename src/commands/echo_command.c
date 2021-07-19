#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "../../libft/libft.h"

// possible strings
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string followed by pipe (|)    )
// ("")
// (		whitespaces         4 dddaaaaaayyyyyys)
// (	""	whitespaces         4 dddaaaaaayyyyyys, with quotes      ")

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

t_bool	check_quotes(const char *input, t_check_quotes *quotes)
{
	quotes->opening = FALSE;
	quotes->closing = FALSE;

	while (*input)
	{
		if (*input == INVERTED_COMMA && quotes->opening)
			quotes->closing = TRUE;
		else
			quotes->opening = TRUE;
		input++;
	}
	if (quotes->opening && quotes->closing)
		return (TRUE);
	return (FALSE);
}

char	*format_string(const char *input)
{
	const int		sub_str_len = get_substr_len(input);
	char			*sub_string;
	char			*trimmed_str;
	t_check_quotes	quotes;

	sub_string = ft_substr(input, 0, sub_str_len);
	if (!sub_string)
		return (NULL);
	trimmed_str = ft_strtrim(sub_string, SPACES_AND_TABS);
	free(sub_string);
	check_quotes(trimmed_str, &quotes);
	if (quotes.opening && quotes.closing)
		printf("we got some openingn and closing quotes\n");
	return (trimmed_str);
}

int	echo_command(const char **input)
{
	char			*str_to_write = format_string(*input);
	int				len = strlen(str_to_write);

	write(1, str_to_write, len);
	write(1, "\n", 1);
	free((char *)str_to_write);
	return (1);
}
