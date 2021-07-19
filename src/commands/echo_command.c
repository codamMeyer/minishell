#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include "../../libft/libft.h"
#include "../parser/parser.h"

// possible strings
// (            String with spaces to trim        )
// (      "string with spaces to trim up to inverted commas"           )
// (    string followed by pipe (|)    )
// ("")
// ( )
// (		whitespace         4 dddaaaaaayyyyyys)
// (	"	whitespace         4 dddaaaaaayyyyyys, with quotes      ")
// (	"	quotes with \"\" quotes"      ")

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

	split_strings = ft_split(clean_str, '\0');
	free((char *)clean_str);
	return (split_strings);
}

char	**parse_echo(const char **input)
{
	const int		sub_str_len = get_substr_len(*input);
	const char		*echo_argv = ft_substr(*input, 0, sub_str_len);
	char			**split_strings;
	char			*trimmed_quotes;
	t_check_quotes	quotes;

	trimmed_quotes = NULL;
	if (!echo_argv)
	{
		printf("here\n");
		return (NULL);
	}
	check_quotes(echo_argv, &quotes);
	if (quotes.opening && quotes.closing)
		split_strings = format_string_with_quotes(echo_argv);
	else
		split_strings = ft_split(echo_argv, 32);
	advance_pointer(input, echo_argv);
	free((char *)echo_argv);
	free(trimmed_quotes);
	return (split_strings);
}

int	echo_command(const char **input)
{
	char			**strings_to_write;
	int				len;
	int				i;

	if (!input || !*input)
		return (-1);
	strings_to_write = parse_echo(input);
	if (!strings_to_write)
	{
		write(1, "\n", 1);
		return (-1);
	}
	i = 0;
	while (strings_to_write[i])
	{
		write(1, &i, sizeof(i));
		len = ft_strlen(strings_to_write[i]);
		write(1, strings_to_write[i], len);
		if (strings_to_write[i + 1])
			write(1, " ", 1);
		i++;
	}
	write(1, "\n", 1);
	free_split(strings_to_write);
	return (1);
}
