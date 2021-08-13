#include <parser/parser.h>
#include <parser/dispatcher.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>

static t_bool	is_valid_last_char(const char *input, int command_len)
{
	const int input_len = ft_strlen(input);
	char	last_char;

	if (input_len >= command_len)
	{
		last_char = input[command_len]; 
		return (isspace(last_char) || last_char == '\0');
	}
	return (FALSE);
}

static t_bool	is_command(const char *input, const char *command)
{
	const int		command_len = ft_strlen(command);

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

int get_arg_len(const char *start)
{
	int len;

	len = 0;
	while (start[len] && start[len] != PIPE)
		++len;
	return (len);
}

t_command	*get_commands(const char **input)
{
	t_command *command_table;
	int	i;
	
	if (!*input)
		return (NULL);
	command_table = malloc(sizeof(t_command) * 1);
	if (!command_table)
		return (NULL);
	i = 0;
	command_table[i].code = get_command_code(input);
	command_table[i].arg.start = *input;
	command_table[i].arg_len = get_arg_len(command_table->arg.start);
	command_table[i].arg.end = *input + command_table[i].arg_len;
	return (command_table);
}

t_bool	parse_input(const char *input)
{
	const t_command *command_table = get_commands(&input);
	if (!command_table)
		return (FALSE);
	dispatch_commands(&input, command_table);
	free((t_command *)command_table);
	return (TRUE);
}




/*

input: echo hello  " | " test | cat -e
output: hello  |  test$

echo_arg: " hello  \" | \" test "

get_command() - echo
input_now: " hello  " | " test | cat -e

find_reserved_char() - | at 0xA

if (!find_reserved_char())
	this the whole string is this command arg       (example: echo        hello)

find_quotes() - start: 0x8  end: 0xC

if (!is_between_quotes(reserved_char_position))
	this is the end of first command arg            (example: echo hello | cat -e)   

else
	is not reserved char in this context
	search again starting from this position + 1. (0xB)  (example: echo    Hello "fake | " | cat -e)


char * input = "echo hello  \" | \" test | cat -e"

t_command{
	code = ECHO;
	first_index = 4;
	last;
}

command_id = 0
cur = 0
while (cur < inp_len)
	{
		cur += get_command_code(&command_table[command_id])   (4 = " hello...")
		command_table[command_id].first_index = cur;
		command_table[command_id].last_index = find_last_index();
		++command_id
		cur = command_table[command_id].last_index
	}


find_last_index(start_index, const char *inp)
{
	char *pipe_position = ft_strchr(&inp[start_index], PIPE)
		if (!pipe_position)
			return inp_len
	while
	{
		char *pipe_position = ft_strchr(&inp[start_index], PIPE)
		pipe_index = pipe_position - inp[0] 
		if (!is_between_quotes(inp, pipe_index))
			return (pipe_index)
		start_index += pipe_index + 1;
	}
	return inp_len
}

is_between_quotes(const char *inp, int pipe_index)
{
	(if quote has \before is just a simple char)
	
	while (end < inp_len)
	{
		quote_start = ft_strchr(inp, ") - inp[0]
		quote_end = ft_strchr(inp[1], ") - inp[0]
		
		if (pipe_index < end)
			TRUE
		inp += end;
	}
	
	FALSE
}



*/
