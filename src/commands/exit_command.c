#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <commands/commands.h>
#include <parser/parser.h>

static	t_bool	has_only_nums(const char *str, int size)
{
	int	i;

	i = 0;
	while (str[i] && i < size)
	{
		if (!ft_isdigit(str[i]) && str[i] != '-')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout)
{
	t_exit_code	exit_code;

	(void)write_to_stdout;
	skip_spaces(&command.arg.start);
	exit_code = ft_atoi(command.arg.start);
	if (!has_only_nums(command.arg.start, command.arg.len))
		printf("BestShellEver: exit: %.*s: numeric argument required\n",
			command.arg.len, command.arg.start);
	else if (exit_code == -1)
		exit_code = 255;
	exit(exit_code);
	return (exit_code);
}
