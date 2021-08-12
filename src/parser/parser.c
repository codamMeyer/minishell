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
	command_table[i].argv = malloc(sizeof(char *));
	command_table[i].argv[0] = (char *)*input;
	command_table[i].input = ft_strdup(*input);
	return (command_table);
}

t_bool	parse_input(const char *input)
{
	const t_command *command_table = get_commands(&input);
	if (!command_table)
		return (FALSE);
	char *input_ptr = command_table->input;
	dispatch_commands(&input, command_table);
	free((t_command *)command_table[0].argv);
	free(input_ptr);
	free((t_command *)command_table);
	return (TRUE);
}
