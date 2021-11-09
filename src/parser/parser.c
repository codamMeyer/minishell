#include <ctype.h>
#include <libft.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <commands/quotes.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/dispatcher.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <errors/errors.h>
#include <signals/signals.h>
#include <arguments.h>

static void	consume_pipe(const char **input, int index)
{
	if (index < 1)
		return ;
	if (**input == PIPE)
		++(*input);
}

t_command	populate_command(const char **input_ptr)
{
	t_command	command;
	t_arg		arg;

	arg.start = *input_ptr;
	arg.len = get_set_index(arg.start, "|");
	arg.end = *input_ptr + arg.len;
	command.files = get_redirection((char **)input_ptr, get_set_index(*input_ptr, "|") - 1);
	command.arguments = split_command_args(arg);
	if (command.arguments)
		command.code = get_command_code(command.arguments[0], &command);
	(*input_ptr) += arg.len;
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
		input_line += commands_table[i].arg.len;
		skip_spaces(&input_line);
		++i;
	}
	return (i);
}

t_bool	parse_input(const char *input)
{
	t_command	commands_table[MAX_CMDS_PER_LINE];
	int			num_commands;
	int			*heredoc_sig;

	num_commands = populate_commands_table(input, commands_table);
	set_exit_code(run_commands(commands_table, num_commands));
	heredoc_sig = heredoc_sigint();
	if (*heredoc_sigint)
		*heredoc_sig = 0;
	cleanup_command_table(commands_table, num_commands);
	return (TRUE);
}
