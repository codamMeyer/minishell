#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>
#include <commands/echo_handle_quotes.h>

void	get_str_without_quotes(const char **input,
								char *stdout_buffer,
								int *buffer_index)
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
		trim_extra_spaces_between_words(input, stdout_buffer, buffer_index);
		cur = *(*input);
	}
	stdout_buffer[*buffer_index] = '\n';
	stdout_buffer[*buffer_index + 1] = '\0';
}

static void	add_space_between_strs(char cur_inp,
								char *stdout_buffer,
								int *buffer_index)
{
	if (cur_inp && \
		stdout_buffer[*buffer_index] != SPACE \
		&& cur_inp != DOUBLE_QUOTES)
	{
		stdout_buffer[*buffer_index] = SPACE;
		++(*buffer_index);
	}
}

static void	get_str_with_quotes(const char **input,
							char *stdout_buffer,
							int *buffer_index)
{
	const t_quotes_position	quotes = get_quotes_positions(*input);
	const int				size = quotes.end - quotes.start;
	const int				num_quotes = 2;

	if (quotes.start && quotes.end)
	{
		ft_memcpy(&stdout_buffer[*buffer_index], quotes.start, size);
		*input += size + num_quotes;
		*buffer_index += size;
		add_space_between_strs(*(*input), stdout_buffer, buffer_index);
	}
	else if (quotes.start)
		++(*input);
}

static int	handle_empty_str(t_bool has_n_flag, t_output_stdout output)
{
	if (has_n_flag)
		output("");
	else
		output("\n");
	return (SUCCESS);
}

int	echo_command(const char **input, t_output_stdout output)
{
	const t_bool	has_n_flag = parse_n_flag(input);
	const int		input_len = ft_strlen(*input);
	char			*stdout_buffer;
	int				buffer_index;

	if (input_len == 0)
		return (handle_empty_str(has_n_flag, output));
	stdout_buffer = ft_calloc(input_len + 2, sizeof(char));
	if (!stdout_buffer)
		return (ERROR);
	buffer_index = 0;
	while (*(*input))
	{
		get_str_with_quotes(input, stdout_buffer, &buffer_index);
		get_str_without_quotes(input, stdout_buffer, &buffer_index);
	}
	if (has_n_flag)
		stdout_buffer[buffer_index] = '\0';
	output(stdout_buffer);
	free(stdout_buffer);
	return (SUCCESS);
}
