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
		len = ft_strlen(strings_to_write[i]);
		write(STDOUT_FILENO, strings_to_write[i], len);
		write_space_between_words(strings_to_write[i + 1]);
		i++;
	}
	return ;
}

int	echo_command(const char **input)
{
	const t_bool	has_n_flag = parse_n_flag(input);
	char			**strings_to_write;

	if (!input || !*input)
		return (ERROR);
	strings_to_write = parse_echo(input);
	if (strings_to_write == NULL)
		return (ERROR);
	write_echo_args((const char **)strings_to_write);
	if (!has_n_flag)
		write(STDOUT_FILENO, "\n", 1);
	free_split(strings_to_write);
	return (SUCCESS);
}
