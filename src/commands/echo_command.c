#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <libft.h>
#include <parser/parser.h>

// possibly add clean-up function for frees()
// possibly split formatting part
char	**parse_echo(const char **input)
{
	const int		sub_str_len = get_substr_len(*input);
	const char		*echo_argv = ft_substr(*input, 0, sub_str_len);
	char			**split_strings;
	char			*trimmed_quotes;
	t_check_quotes	quotes;

	trimmed_quotes = NULL;
	if (!echo_argv)
		return (NULL);
	if (has_inverted_comma_set(echo_argv, &quotes))
		split_strings = format_string_with_quotes(echo_argv);
	else
		split_strings = ft_split(echo_argv, SPACE);
	advance_pointer(input, echo_argv);
	free((char *)echo_argv);
	free(trimmed_quotes);
	return (split_strings);
}

void	write_echo_args(const char **strings_to_write)
{
	int	i;
	int	len;

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
	return ;
}

int	echo_command(const char **input)
{
	char			**strings_to_write;

	if (!input || !*input)
		return (-1);
	strings_to_write = parse_echo(input);
	if (strings_to_write == NULL)
		return (-1);
	write_echo_args((const char **)strings_to_write);
	write(1, "\n", 1);
	free_split(strings_to_write);
	return (1);
}
