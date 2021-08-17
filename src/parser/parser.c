#include <parser/parser.h>
#include <parser/dispatcher.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <commands/echo_handle_quotes.h>

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

static t_bool	is_command(const char *input, const char *command)
{
	const int	command_len = ft_strlen(command);

	return (strncmp(input, command, command_len) == 0
		&& is_valid_last_char(input, command_len));
}

t_command_code	get_command_code(const char **input)
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
		if (is_command(*input, commands[command_code]))
		{
			advance_pointer(input, commands[command_code]);
			return (command_code);
		}
		++command_code;
	}
	return (INVALID);
}

t_bool	is_between_quotes(const char *input, int reserved_char_index)
{
	t_quotes_index	quotes;
	int				offset;
	char			*new_pos;

	offset = 0;
	new_pos = (char *)input;
	while (new_pos)
	{
		quotes = get_quotes_indexes(new_pos);
		if (!quotes.start && !quotes.end)
			return (FALSE);
		if (quotes.start + offset < reserved_char_index
			&& quotes.end + offset > reserved_char_index)
			return (TRUE);
		offset += quotes.end;
		new_pos = (char *)&input[quotes.end + offset];
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

int	check_for_pipe(const char **input)
{
	if (ft_strncmp("| ", *input, 2) == 0)
	{
		*input += 2;
		return (1);
	}
	return (0);
}

/* display sintax error when necessary */
t_command	populate_command(const char **input_ptr)
{
	t_command	command;

	command.code = get_command_code(input_ptr);
	if (command.code == INVALID)
		return (command);
	command.arg.start = *input_ptr;
	command.arg_len = get_arg_len(command.arg.start);
	command.arg.end = *input_ptr + command.arg_len;
	return (command);
}

/* need to decide how to handle pipes */
t_command	*get_commands(const char *input, int *num_commands)
{
	const char	*input_line = input;
	t_command	*command_table;
	int			pipe_count;
	int			i;

	if (!input || !*input)
		return (NULL);
	command_table = malloc(sizeof(t_command) * MAX_CMDS_PER_LINE);
	if (!command_table)
		return (NULL);
	i = 0;
	pipe_count = 0;
	while (*input_line)
	{
		if (i > 0)
			pipe_count += check_for_pipe(&input_line);
		command_table[i] = populate_command(&input_line);
		if (command_table[i].code == INVALID)
			break ;
		input_line += command_table[i].arg_len;
		++i;
	}
	*num_commands = i;
	return (command_table);
}

t_bool	parse_input(const char *input)
{
	int				num_commands;
	const t_command	*command_table = get_commands(input, &num_commands);

	if (!command_table)
		return (FALSE);
	dispatch_commands(&input, command_table, num_commands);
	free((t_command *)command_table);
	return (TRUE);
}
