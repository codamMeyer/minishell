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

t_arg	get_str_without_quotes(t_arg echo_arg,
								char *stdout_buffer,
								int *buffer_index)
{
	char	cur;

	skip_spaces(&echo_arg.start);
	if (is_double_quote(*echo_arg.start))
		return (echo_arg);
	cur = *echo_arg.start;
	while (cur && !is_double_quote(cur) && echo_arg.start < echo_arg.end)
	{
		if (isspace(cur))
			trim_extra_spaces_between_words(&echo_arg, \
										stdout_buffer, \
										buffer_index);
		else
		{
			stdout_buffer[*buffer_index] = cur;
			++(*buffer_index);
			++(echo_arg.start);
		}
		cur = *echo_arg.start;
	}
	stdout_buffer[*buffer_index] = '\n';
	stdout_buffer[*buffer_index + 1] = '\0';
	return (echo_arg);
}

static void	add_space_between_strs(char cur_inp,
								char *stdout_buffer,
								int *buffer_index)
{
	if (cur_inp && \
		stdout_buffer[*buffer_index] != SPACE
		&& cur_inp != DOUBLE_QUOTES)
	{
		stdout_buffer[*buffer_index] = SPACE;
		++(*buffer_index);
	}
}

static t_arg	get_str_with_quotes(t_arg arg,
							char *stdout_buffer,
							int *buffer_index)
{
	const t_quotes_position	quotes = get_quotes_positions(arg.start);
	const int				size = quotes.end - quotes.start;
	const int				num_quotes = 2;

	if (quotes.start && quotes.end)
	{
		ft_memcpy(&stdout_buffer[*buffer_index], quotes.start, size);
		arg.start += size + num_quotes;
		*buffer_index += size;
		add_space_between_strs(*arg.start, stdout_buffer, buffer_index);
	}
	else if (quotes.start)
		++arg.start;
	return (arg);
}

static int	handle_empty_str(t_bool has_n_flag, t_output_stdout output)
{
	if (has_n_flag)
		output("");
	else
		output("\n");
	return (SUCCESS);
}

t_exit_code	echo_command(t_command command, t_output_stdout output)
{
	const t_bool	has_n_flag = parse_n_flag((t_arg *)&command.arg);
	char			*stdout_buffer;
	int				buffer_index;

	if (command.arg_len == 0)
		return (handle_empty_str(has_n_flag, output));
	stdout_buffer = ft_calloc(command.arg_len + 2, sizeof(char));
	if (!stdout_buffer)
		return (ERROR);
	buffer_index = 0;
	while (command.arg.start < command.arg.end)
	{
		command.arg = get_str_with_quotes(command.arg, \
											stdout_buffer, \
											&buffer_index);
		command.arg = get_str_without_quotes(command.arg, \
												stdout_buffer, \
												&buffer_index);
	}
	if (has_n_flag)
		stdout_buffer[buffer_index] = '\0';
	output(stdout_buffer);
	free(stdout_buffer);
	return (SUCCESS);
}
