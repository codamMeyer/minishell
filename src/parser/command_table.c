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

char	*get_redirection_position(const char *set, char *str_to_check)
{
	int i;

	i = 0;
	while (str_to_check[i])
	{
		if (ft_strchr(set, str_to_check[i]))
			return (&str_to_check[i]);
		++i;
	}
	return (&str_to_check[i]);
}

int	get_arg_len(const char *start)
{
	char	*redirection_position;
	int		pipe_index;
	int		start_index;

	start_index = 0;
	redirection_position = get_redirection_position(REDIRECTION_CHARS, (char *)start);
	while (redirection_position && start[start_index] != '\0')
	{
		pipe_index = redirection_position - &start[0];
		if (!is_between_quotes(start, pipe_index))
			return (pipe_index);
		start_index += pipe_index + 1;
		redirection_position = ft_strchr(&start[start_index], PIPE);
	}
	return (ft_strlen(start));
}
