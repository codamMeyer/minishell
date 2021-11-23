#include <libft.h>
#include <executor/run_commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <signals/signals.h>
#include <parser/arguments.h>

static void	consume_pipe(const char **input, int index)
{
	if (index < 1)
		return ;
	if (**input == PIPE)
		++(*input);
}

void	skip_spaces(const char **input)
{
	while (*input && ft_isspace(*(*input)))
		++(*input);
}

t_command	populate_command(const char **input_ptr)
{
	t_command	command;
	t_arg		arg;

	arg.start = *input_ptr;
	arg.len = get_set_index(arg.start, "|");
	arg.end = *input_ptr + arg.len;
	command.files = get_redirection((char **)input_ptr, arg.len - 1);
	command.arguments = split_command_args(arg);
	if (!command.arguments)
		handle_error(MALLOC_ERROR, MALLOC_STR, NULL);
	command.code = get_command_code(command.arguments[0], &command);
	(*input_ptr) += arg.len;
	return (command);
}

int	populate_commands_table(const char *input, t_command commands_table[])
{
	int			i;

	if (!input)
		return (0);
	i = 0;
	while (*input)
	{
		consume_pipe(&input, i);
		commands_table[i] = populate_command(&input);
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
