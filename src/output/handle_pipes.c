#include "handle_pipes.h"
// #include <commands/commands.h>
#include <string.h>
#include <stdio.h>
#define MAX_CMDS_PER_LINE 100

/*
	assuming the full unknown command is passed with full checked executable
	path as this is already checked when parsing to see if given
	command is valid ex:
		commands->arg->start = "...[c]at -e main..."
		command->arg->end = "...cat -e mai[n]..."
		command->exe_path = "/bin/cat"
*/

typedef struct s_arg
{
	const char	*start;
	const char	*end;
}	t_arg;

typedef struct s_command
{
	t_arg			arg;
	int				arg_len;
	const char		*exe_path;
}	t_command;

void	create_table(t_command *command, char *arg, char *path)
{
	command->arg.start = arg;
	command->arg_len = strlen(arg);
	command->exe_path = path;
}

int	handle_pipes(t_command *commands[MAX_CMDS_PER_LINE],
				int num_of_commands, const char *env[])
{

	return (1);
}

int main(int argc, char *argv[], char *env[])
{
	t_command commands[MAX_CMDS_PER_LINE];
	int number_of_commands = 3;

	create_table(&commands[0], "cat main", "/bin/cat");
	create_table(&commands[1], "grep int", "/usr/bin/grep");
	create_table(&commands[2], "cat -e", "/bin/cat");
	while (number_of_commands > 0)
	{
		printf("%s\n", commands[number_of_commands].arg.start);
		--number_of_commands;
	}
}
