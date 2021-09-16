#include "commands.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <libft.h>
#include <parser/parser.h>
#include <commands/echo_utils.h>
#include <commands/quotes.h>
#include <commands/buffer.h>
#include <env/env_utils.h>

t_arg	append_char_to_buffer(t_arg arg, t_buffer *buffer)
{
	buffer->buf[buffer->index] = *arg.start;
	++(buffer->index);
	++(arg.start);
	return (arg);
}

void	append_value_to_buffer(t_arg *echo_arg, t_buffer *buffer)
{
	t_env	*var;
	int		key_len;
	int		value_len;

	++(echo_arg->start);
	value_len = 0;
	key_len = get_key_len(echo_arg->start);
	var = find_variable(get_environment(), echo_arg->start);
	if (var)
	{
		value_len = ft_strlen(var->value);
		ft_strlcpy(&buffer->buf[buffer->index], var->value, value_len + 1);
	}
	echo_arg->start = echo_arg->start + key_len;
	buffer->index += value_len;
}

void	handle_spaces(t_arg *echo_arg, t_buffer *buffer)
{
	if (isspace(*echo_arg->start) && buffer->index)
	{
		buffer->buf[buffer->index] = SPACE;
		++(buffer->index);
	}
	skip_spaces(&echo_arg->start);
}

t_arg	get_str_without_quotes(t_arg echo_arg, t_buffer *buffer)
{
	char	cur;

	cur = *echo_arg.start;
	if (is_quote(cur))
		return (echo_arg);
	while (cur && !is_quote(cur) && echo_arg.start < echo_arg.end)
	{
		if (isspace(cur))
			trim_extra_spaces_between_words(&echo_arg, buffer);
		else if (is_variable(cur))
			append_value_to_buffer(&echo_arg, buffer);
		else
			echo_arg = append_char_to_buffer(echo_arg, buffer);
		cur = *echo_arg.start;
	}
	return (echo_arg);
}

t_arg	get_str_with_quotes(t_arg arg, t_buffer *buffer)
{
	const t_quotes_position	quotes = get_quotes_positions(arg.start);

	if (quotes.start && quotes.end)
	{
		arg.start = quotes.start;
		while (arg.start < quotes.end)
		{
			if (quotes.is_double_quote && is_variable(*arg.start))
				append_value_to_buffer(&arg, buffer);
			else
				arg = append_char_to_buffer(arg, buffer);
		}
		++arg.start;
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
	t_buffer		buffer;

	init_buffer(&buffer);
	if (command.arg_len == 0)
		return (handle_empty_str(has_n_flag, output));
	while (command.arg.start < command.arg.end)
	{
		command.arg = get_str_with_quotes(command.arg, &buffer);
		handle_spaces(&command.arg, &buffer);
		command.arg = get_str_without_quotes(command.arg, &buffer);
	}
	if (!has_n_flag)
		buffer.buf[buffer.index] = '\n';
	output(&buffer.buf[0]);
	return (SUCCESS);
}
