#include <parser/parser.h>
#include <parser/command_table.h>
#include <parser/dispatcher.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <commands/echo_handle_quotes.h>
#include <commands/echo_utils.h>
#include <output/handle_pipes.h>


static void	consume_pipe(const char **input, int index)
{
	if (index < 1)
		return ;
	if (ft_strncmp("|", *input, 1) == 0)
		++(*input);
}

/* display syntax error when necessary */
t_command	populate_command(const char **input_ptr)
{
	t_command	command;

	command.code = get_command_code(input_ptr);
	command.arg.start = *input_ptr;
	if (command.code == INVALID)
		return (command);
	command.arg_len = get_arg_len(command.arg.start);
	command.arg.end = *input_ptr + command.arg_len;
	return (command);
}

/* need to decide how to handle pipes */
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
		if (commands_table[i].code == INVALID)
		{
			++i;
			break ;
		}
		input_line += commands_table[i].arg_len;
		++i;
	}
	return (i);
}

t_bool	parse_input(const char *input)
{
	t_command	commands_table[MAX_CMDS_PER_LINE];
	int			num_commands;

	num_commands = populate_commands_table(input, commands_table);
	handle_pipes(commands_table, num_commands, NULL);
	// dispatch_commands(commands_table, num_commands);
	return (TRUE);
}
