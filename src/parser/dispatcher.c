#include <parser/dispatcher.h>
#include <commands/commands.h>
#include <commands/echo_utils.h>
#include <parser/parser.h>
#include <stdio.h>
#include <libft.h>
#include <ctype.h>

static void	copy_unknown_command_to_buffer(const char **input, char buffer[])
{
	const char	*cur = *input;
	int		i;

	i = 0;
	while (cur[i] && !isspace(cur[i]))
		++i;
	ft_memcpy(buffer, cur, i);
	buffer[i] = '\0';
}

t_bool	unknown_command(const char **input, t_output_stdout output)
{
	const char	*shell_name = "BestShellEver: ";
	const char	*command_not_found = ": command not found\n";
	char		unknown_command_str[4096];

	skip_spaces(input);
	copy_unknown_command_to_buffer(input, &unknown_command_str[0]);
	output(shell_name);
	output(&unknown_command_str[0]);
	output(command_not_found);
	return (FALSE);
}

t_bool	dispatch_commands(const char **input, \
							const t_command *command_table, \
							int num_commands)
{
	int	i;

	i = 0;
	while (i < num_commands)
	{
		if (command_table[i].code == EXIT)
			exit_command(SUCCESS);
		else if (command_table[i].code == ECHO)
			echo_command(command_table[i], write_to_stdout);
		else if (command_table[i].code == PWD)
			pwd_command(write_to_stdout);
		else if (command_table[i].code == INVALID)
			unknown_command(input, write_to_stdout);
		else if (command_table[i].code == EMPTY_LINE)
			return (TRUE);
		++i;
	}
	return (FALSE);
}


/*

void empty_command(t_command command, t_output_stdout write_to_stdout)
{
	(void)command;
	(void)write_to_stdout;
}

typedef void(*t_command_function)(t_command, t_output_stdout);

t_command_function commands[LAST] = {
										empty_command,
										echo_command,
										exit_command,
										pwd_command,
									}

*/