#include <ctype.h>
#include <libft.h>
#include <stdio.h>
#include <commands/quotes.h>
#include <parser/command_table.h>
#include <parser/get_executable_path.h>
#include <parser/parser.h>

static t_bool	is_valid_last_char(const char *input, int command_len)
{
	const int	input_len = ft_strlen(input);
	char		last_char;

	if (input_len >= command_len)
	{
		last_char = input[command_len];
		return (isspace(last_char) || last_char == NULL_TERMINATOR);
	}
	return (FALSE);
}

static t_bool	is_built_in_command(const char *input, const char *command)
{
	const int	command_len = ft_strlen(command);

	return (ft_strncmp(input, command, command_len) == 0
		&& is_valid_last_char(input, command_len));
}

/*
	Added checks to see if it's a system of built-in command
*/
t_command_code	get_command_code(const char **input, t_command *command)
{
	static const char	*commands[LAST] = {"", "echo", "exit", "pwd",
											"export", "unset", "env",
											"cd" ,"invalid"
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

int	get_set_index(const char *start, const char *set)
{
	char	*redirection_position;
	int		redirection_index;
	int		start_index;

	start_index = 0;
	redirection_position = get_set_position(set,
			(char *)start);
	while (redirection_position && start[start_index] != '\0')
	{
		redirection_index = redirection_position - &start[0];
		if (!is_between_quotes(start, redirection_index))
			return (redirection_index);
		start_index += redirection_index + 1;
		redirection_position = get_set_position(set,
				(char *)&start[start_index]);
	}
	return (ft_strlen(start));
}
