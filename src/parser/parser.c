#include "parser.h"
#include <parser/command_table.h>
#include <parser/dispatcher.h>
#include <parser/parse_redirection.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <commands/echo_handle_quotes.h>
#include <commands/echo_utils.h>
#include <executor/run_commands.h>

static void	consume_pipe(const char **input, int index)
{
	if (index < 1)
		return ;
	if (**input == PIPE)
		++(*input);
}

/* 
	TODO: Display syntax error when necessary
 */
t_command	populate_command(const char **input_ptr)
{
	t_command	command;

	printf("PARSING: %s\n", *input_ptr);
	command.files = get_redirection((char **)input_ptr,
			get_arg_len(*input_ptr, "|"));
	command.code = get_command_code(input_ptr, &command);
	command.arg.start = *input_ptr;
	command.arg_len = get_arg_len(command.arg.start, "|");
	command.arg.end = *input_ptr + command.arg_len;
	printf("AFTERPARSING: %s\n", command.arg.end);
	return (command);
}

int	populate_commands_table(const char *input, t_command commands_table[])
{
	const char	*input_line = input;
	int			i;

	if (!input)
		return (0);
	i = 0;
	while (*input_line)
	{
		consume_pipe(&input_line, i);
		commands_table[i] = populate_command(&input_line);
		input_line += commands_table[i].arg_len;
		skip_spaces(&input_line);
		++i;
	}
	return (i);
}

t_bool	parse_input(const char *input, char *env[])
{
	t_command	commands_table[MAX_CMDS_PER_LINE];
	int			num_commands;

	num_commands = populate_commands_table(input, commands_table);
	run_commands(commands_table, num_commands, env);
	return (TRUE);
}
