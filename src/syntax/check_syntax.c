#include <defines.h>
#include <commands/commands.h>
#include <parser/command_table.h>
#include <parser/parser.h>
#include <libft.h>
#include <ctype.h>
#include <stdio.h>

t_bool	is_valid_angled_brackets_syntax(const char *input)
{
	(void)input;
	return (TRUE);
}

t_bool	only_contains_white_space_after_pipe(const char *str)
{
	if (*str)
		++str;
	while (str && *str)
	{
		if (!isspace(*str))
			return (FALSE);
		++str;
	}
	return (TRUE);
}

t_bool	is_valid_pipes_syntax(const char *input)
{
	const int	len = ft_strlen(input);
	int			i;

	i = 0;
	while (input && input[i])
	{
		skip_spaces(&input);
		i += get_arg_len(&input[i], "|");
		if (i == len && input[i] != PIPE)
			break ;
		else if (i == 0)
			return (FALSE);
		while (input[i] && isspace(input[i + 1]))
			i++;
		if (input[i + 1] == PIPE)
			return (FALSE);
		else if (only_contains_white_space_after_pipe(&input[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

t_bool	is_valid_syntax(const char *input)
{
	if (!is_valid_pipes_syntax(input))
		return (FALSE);
	else if (!is_valid_angled_brackets_syntax(input))
		return (FALSE);
	return (TRUE);
}
