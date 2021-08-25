#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/get_executable_path.h>
#include <commands/echo_handle_quotes.h>
#include <libft.h>
#include <stdio.h>
#include <ctype.h>

static t_bool	is_valid_last_char(const char *input, int command_len)
{
	const int	input_len = ft_strlen(input);
	char		last_char;

	if (input_len >= command_len)
	{
		last_char = input[command_len];
		return (isspace(last_char) || last_char == '\0');
	}
	return (FALSE);
}

static t_bool	is_built_in_command(const char *input, const char *command)
{
	const int	command_len = ft_strlen(command);

	return (ft_strncmp(input, command, command_len) == 0
		&& is_valid_last_char(input, command_len));
}

int	get_cmd_len(const char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != SPACE)
		i++;
	return (i);
}

t_bool	is_system_command(const char *input, t_command *command)
{
	const int	arg_len = get_cmd_len(input);
	char		cmd_buffer[4098];

	ft_strlcpy(&cmd_buffer[0], input, arg_len + 1);
	command->exe_path = get_executable_path(&cmd_buffer[0]);
	if (command->exe_path)
		return (TRUE);
	return (FALSE);
}

t_command_code	get_command_code(const char **input, t_command *command)
{
	static const char	*commands[LAST] = {
											"",
											"echo",
											"exit",
											"pwd",
											"invalid"
										};
	t_command_code		command_code;

	skip_spaces(input);
	command_code = EMPTY_LINE;
	while (command_code < INVALID)
	{
		if (is_built_in_command(*input, commands[command_code]))
		{
			advance_pointer(input, commands[command_code]);
			return (command_code);
		}
		++command_code;
	}
	if (is_system_command(*input, command))
		return (SYSTEM);
	return (INVALID);
}

t_bool	is_between_quotes(const char *input, int reserved_char_index)
{
	t_quotes_index	quotes;
	char			*new_pos;

	new_pos = (char *)input;
	while (new_pos)
	{
		quotes = get_quotes_indexes(new_pos);
		if (!quotes.start && !quotes.end)
			return (FALSE);
		if (quotes.start < reserved_char_index
			&& quotes.end > reserved_char_index)
			return (TRUE);
		new_pos = &new_pos[quotes.end + 1];
	}
	return (FALSE);
}

int	get_arg_len(const char *start)
{
	char	*pipe_position;
	int		pipe_index;
	int		start_index;

	start_index = 0;
	pipe_position = ft_strchr(start, PIPE);
	while (pipe_position && start[start_index] != '\0')
	{
		pipe_index = pipe_position - &start[0];
		if (!is_between_quotes(start, pipe_index))
			return (pipe_index);
		start_index += pipe_index + 1;
		pipe_position = ft_strchr(&start[start_index], PIPE);
	}
	return (ft_strlen(start));
}
