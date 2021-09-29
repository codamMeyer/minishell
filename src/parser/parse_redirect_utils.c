#include <fcntl.h>
#include <stdio.h>
#include <commands/commands.h>
#include <executor/executor_utils.h>
#include <parser/command_table.h>
#include <parser/parse_redirection.h>

void	replace_redirection_w_space(char **input, int len, int start)
{
	int	i;

	i = 0;
	while (i < len && (*input)[start + i] != NULL_TERMINATOR)
	{
		(*input)[start + i] = SPACE_CHAR;
		++i;
	}
}

int	count_consecutive_spaces(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i] && str[i] == SPACE_CHAR)
		++i;
	return (i);
}

t_bool	is_multi_angled_bracket(const int redirection_id)
{
	return (redirection_id == FT_APPEND || redirection_id == HERE_DOC
		|| redirection_id == DIAMOND_BRACKETS);
}
