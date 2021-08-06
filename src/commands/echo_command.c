#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h> 
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>

// possibly add clean-up function for frees()
// possibly split formatting part

void	echo_stdout(const char *string_to_write, int len)
{
	write(STDOUT_FILENO, string_to_write, len);
}

void	trim_spaces_between_words(const char **input, char *stdout_buffer, int *buffer_index)
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

void	get_str_without_quotes(const char **input, char *stdout_buffer, int *buffer_index)
{
	char	cur;

	skip_spaces(input);
	if (is_double_quote(*(*input)))
		return ;
	cur = *(*input);
	while (cur && !is_double_quote(cur))
	{
		stdout_buffer[*buffer_index] = cur;
		++(*buffer_index);
		++(*input);
		trim_spaces_between_words(input, stdout_buffer, buffer_index);
		cur = *(*input);
	}
	stdout_buffer[*buffer_index] = '\n';
}

t_quotes_position	get_quotes_positions(const char *input)
{
	t_quotes_position quotes_position;

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

void	get_str_with_quotes(const char **input, char *stdout_buffer, int *buffer_index)
{
	t_quotes_position	quotes = get_quotes_positions(*input);
	int size = quotes.end - quotes.start;
	if (quotes.start && quotes.end)
	{
		strncpy(&stdout_buffer[*buffer_index], quotes.start, size);
		*input += size + 2;
		*buffer_index += size;
		if (*(*input) && stdout_buffer[*buffer_index] != ' ' && *(*input) != DOUBLE_QUOTES)
		{
			stdout_buffer[*buffer_index] = ' ';
			++(*buffer_index);
		}
	}
	else if (quotes.start)
		++(*input);
}

int	echo_command(const char **input, t_output_stdout output)
{
	const t_bool	has_n_flag = parse_n_flag(input);
	const int		input_len = ft_strlen(*input);
	char			*stdout_buffer;
	int				i;

	if (input_len == 0)
	{
		if (has_n_flag)
			output("", 1);
		else
			output("\n", 1);
		return (SUCCESS);
	}
	stdout_buffer = malloc(input_len * sizeof(char));
	ft_bzero(stdout_buffer, input_len);
	if (!stdout_buffer)
		return (ERROR);
	i = 0;
	while (*(*input))
	{
		get_str_with_quotes(input, stdout_buffer, &i);
		get_str_without_quotes(input, stdout_buffer, &i);
	}
	if (has_n_flag)
		stdout_buffer[i] = '\0';
	++i;
	output(stdout_buffer, i);
	free(stdout_buffer);
	return (SUCCESS);
}

// int	echo_command(const char **input, t_output_stdout output)
// {
// 	const t_bool	has_n_flag = parse_n_flag(input);
// 	const char		*echo_argv = get_echo_args(input);
// 	char			**strings_to_write;

// 	if (!echo_argv)
// 		return (ERROR);
// 	strings_to_write = format_echo_args(echo_argv);
// 	if (strings_to_write == NULL)
// 		return (ERROR);
// 	output((const char **)strings_to_write);
// 	if (!has_n_flag)
// 		write(STDOUT_FILENO, "\n", 1);
// 	free_split(strings_to_write);
// 	free((char *)echo_argv);
// 	return (SUCCESS);
// }