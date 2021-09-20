#include <commands/commands.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>

/*
	This'll probably change, saving for syntax checker
*/
void	check_cmd_str_validity(char *cmd_str)
{
	int	i;

	i = 0;
	while (cmd_str && cmd_str[i])
	{
		if (cmd_str[i] == DOUBLE_QUOTES)
		{
			i++;
			while (cmd_str[i] && cmd_str[i] != DOUBLE_QUOTES)
				i++;
		}
		if (i > 0 && cmd_str[i + 1] == RIGHT_ANGLE && cmd_str[i] != SPACE)
			handle_errors(16, "Syntax error in checker for outfile");
		i++;
	}
}

void	replace_redirection_w_space(char **input, int len, int start)
{
	int	i;

	i = 0;
	while (i < len)
	{
		(*input)[start + i] = SPACE;
		++i;
	}
}

int	count_consecutive_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == SPACE)
		i++;
	return (i);
}
