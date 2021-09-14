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
#include <env/env_utils.h>

void	append_value_to_buffer(t_arg *echo_arg,
								char *stdout_buffer,
								int *buffer_index)
{
	t_env	*var;
	int		key_len;
	int 	value_len;
	
	++(echo_arg->start);
	value_len = 0;
	key_len = get_key_len(echo_arg->start);	
	var = find_variable(get_environment(), echo_arg->start);
	if (var)
	{
		value_len = ft_strlen(var->value);
		ft_strlcpy(&stdout_buffer[*buffer_index], var->value, value_len + 1);
	}
	echo_arg->start = echo_arg->start + key_len;
	*buffer_index += value_len;
}


t_arg	get_str_without_quotes(t_arg echo_arg,
								char *stdout_buffer,
								int *buffer_index)
{
	char	cur;

	if (isspace(*echo_arg.start) && !is_double_quote(*echo_arg.start) && *buffer_index)
	{
		stdout_buffer[*buffer_index] = SPACE;
		++(*buffer_index);
	}
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
		else if (cur == '$')
			append_value_to_buffer(&echo_arg, stdout_buffer, buffer_index);
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

// static void	add_space_between_strs(t_arg arg,
// 								char *stdout_buffer,
// 								int *buffer_index)
// {
// 	if (arg.start < arg.end && \
// 		stdout_buffer[*buffer_index] != SPACE
// 		&& (is_double_quote(*arg.start) || is_single_quote(*arg.start)))
// 	{
// 		stdout_buffer[*buffer_index] = SPACE;
// 		++(*buffer_index);
// 	}
// }

t_arg	get_str_with_quotes(t_arg arg,
							char *stdout_buffer,
							int *buffer_index)
{
	const t_quotes_position	quotes = get_quotes_positions(arg.start);

	if (quotes.start && quotes.end)
	{
		arg.start = quotes.start;
		while (arg.start < quotes.end)
		{
			if (quotes.is_double_quote && *arg.start == '$')
				append_value_to_buffer(&arg, stdout_buffer, buffer_index);
			else
			{
				stdout_buffer[*buffer_index] = *arg.start;
				++(*buffer_index);
				++(arg.start);
			}
		}
		arg.start = quotes.end + 1;
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
	char			stdout_buffer[2049];
	int				buffer_index;

	if (command.arg_len == 0)
		return (handle_empty_str(has_n_flag, output));
	ft_bzero(stdout_buffer, sizeof(stdout_buffer));
	buffer_index = 0;
	while (command.arg.start < command.arg.end)
	{
		command.arg = get_str_with_quotes(command.arg, \
											&stdout_buffer[0], \
											&buffer_index);
		command.arg = get_str_without_quotes(command.arg, \
												&stdout_buffer[0], \
												&buffer_index);
	}
	if (has_n_flag)
		stdout_buffer[buffer_index] = '\0';
	output(&stdout_buffer[0]);
	return (SUCCESS);
}
