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

typedef struct s_quotes_index
{
	int	start;
	int	end;
}	t_quotes_index;

t_quotes_index	get_quotes_pair_position(const char *input)
{
	char			*start;
	t_quotes_index	quotes;

	start = ft_strchr(input, DOUBLE_QUOTES);
	if (start)
	{
		quotes.start = start - &input[0];
		quotes.end = ft_strchr(&input[quotes.start + 1], DOUBLE_QUOTES) - &input[0];
		return (quotes);
	}
	quotes.start = 0;
	quotes.end = 0;
	return (quotes);
}

t_bool	is_between_quotes(const char *input, int pipe_index)
{
	t_quotes_index	quotes;
	int				offset;
	char			*new_pos;

	quotes = get_quotes_pair_position(input);
	if (quotes.start < pipe_index && quotes.end > pipe_index)
		return (TRUE);
	if (!quotes.start && !quotes.end)
		return (FALSE);
	offset = &(input[quotes.end + 1]) - &input[0];
	new_pos = (char *)&(input[quotes.end + 1]);
	while (new_pos)
	{
		quotes = get_quotes_pair_position(new_pos);
		if (!quotes.start && !quotes.end)
			return (FALSE);
		if (quotes.start + offset < pipe_index && quotes.end + offset > pipe_index)
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

	pipe_position = ft_strchr(start, PIPE);
	if (!pipe_position)
		return (ft_strlen(start));
	start_index = 0;
	while (start[start_index] != '\0')
	{
		pipe_index = pipe_position - &start[0];
		if (!is_between_quotes(start, pipe_index))
			return (pipe_index);
		start_index += pipe_index + 1;
		pipe_position = ft_strchr(&start[start_index], PIPE);
		if (!pipe_position)
			break ;
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

t_command	*get_commands(const char *input, int *num_commands)
{
	t_command	*command_table;
	const char	*input_ptr = input;
	int			pipe_count;
	int			i;
	
	if (!input || !*input)
		return (NULL);
	command_table = malloc(sizeof(t_command) * 100);
	if (!command_table)
		return (NULL);
	i = 0;
	pipe_count = 0;
	while (*input_ptr)
	{
		if (i > 0)
			pipe_count += check_for_pipe(&input_ptr);
		command_table[i].code = get_command_code(&input_ptr);
		if (command_table[i].code == INVALID)
			break ;// display sintax error when necessary
		command_table[i].arg.start = input_ptr;
		command_table[i].arg_len = get_arg_len(command_table[i].arg.start);
		command_table[i].arg.end = input_ptr + command_table[i].arg_len;
		input_ptr += command_table[i].arg_len;
		++i;
	}
	*num_commands = i;
	return (command_table);
}

t_bool	parse_input(const char *input)
{
	int				num_commands;
	const t_command	*command_table = get_commands(input, &num_commands);

	if (!input)
		return (FALSE);
	if (!command_table)
		return (FALSE);
	dispatch_commands(&input, command_table, num_commands);
	free((t_command *)command_table);
	return (TRUE);
}
