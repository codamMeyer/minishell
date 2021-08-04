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
char	*get_echo_args(const char **input)
{
	int		sub_str_len;
	char	*echo_argv;

	if (!input || !*input)
		return (NULL);
	sub_str_len = get_substr_len(*input);
	echo_argv = ft_substr(*input, 0, sub_str_len);
	advance_pointer(input, echo_argv);
	return (echo_argv);
}

char	**format_echo_args(const char *echo_argv)
{
	char			**split_strings;
	t_check_quotes	quotes;

	if (has_double_quotes_set(echo_argv, &quotes))
		split_strings = format_string_with_quotes(echo_argv);
	else
		split_strings = ft_split(echo_argv, SPACE);
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

void	echo_stdout(const char *string_to_write, int len)
{
	write(STDOUT_FILENO, string_to_write, len);
}


void get_str_without_quotes(const char **input, char *stdout_buffer, int *buffer_index)
{
	char cur;
	
	skip_spaces(input);
	cur = *(*input);
	if (cur == DOUBLE_QUOTES)
		return ;
	while (cur != DOUBLE_QUOTES && cur != '\0')
	{
		stdout_buffer[*buffer_index] = cur;
		++(*input);
		if (isspace(*(*input)))
		{
			++(*buffer_index);
			stdout_buffer[*buffer_index] = SPACE;
			skip_spaces(input);
		}	
		cur = *(*input);
		++(*buffer_index);
	}
	if (cur == '\0' && stdout_buffer[*buffer_index - 1] == SPACE)
		stdout_buffer[*buffer_index - 1] = '\0';
	else
	{
		stdout_buffer[*buffer_index] = '\n';
		stdout_buffer[*buffer_index + 1] = '\0';
	}
}

void get_str_with_quotes(const char **input, char *stdout_buffer, int *buffer_index)
{
	char cur;
	cur = *(*input);
	if (cur != DOUBLE_QUOTES)
		return ;
	++(*input);
	cur = *(*input);
	while (cur != '\0')
	{
		stdout_buffer[*buffer_index] = cur;
		++(*input);
		cur = *(*input);
		++(*buffer_index);
		if (cur == DOUBLE_QUOTES)
		{
			if (*(*input + 1) == '\0')
			{
				stdout_buffer[*buffer_index] = '\n';
				return ;
			}
			else
				stdout_buffer[*buffer_index] = ' ';
			++(*buffer_index);
			++(*input);
			return ;
		}
	}
	if (cur == '\0' && stdout_buffer[*buffer_index - 1] == SPACE)
		stdout_buffer[*buffer_index - 1] = '\0';
	else
		stdout_buffer[*buffer_index] = '\n';
}

int	echo_command(const char **input, t_output_stdout output)
{
	const t_bool	has_n_flag = parse_n_flag(input);
	const int	input_len = ft_strlen(*input);
	char	*stdout_buffer;
	int		i;

	if (input_len == 0)
	{
		if (has_n_flag)
			output("", 1);
		else
			output("\n", 1);
		return (SUCCESS);
	}
	stdout_buffer = malloc(input_len * sizeof(char));
	if (!stdout_buffer)
		return (ERROR);
	i = 0;
	while (*(*input))
	{
		get_str_with_quotes(input, stdout_buffer, &i);
		get_str_without_quotes(input, stdout_buffer, &i);
	}
	if (has_n_flag)
	{
		stdout_buffer[i] = '\0';
		++i;
	}
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