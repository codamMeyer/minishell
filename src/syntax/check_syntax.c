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
	const int	len  = ft_strlen(input);
	int			i;

	i = 0;
	while (input && input[i] && i < len)
	{
		skip_spaces(&input);
		i += get_arg_len(&input[i], "|");
		printf("\ni = %d\nlen = %d\n", i, len);
		if (i == len && input[i] != PIPE)
			break ;
		if (input[i + 1] == PIPE)
		{
			printf("\nDOUBLE PIPES\n");
			return (FALSE);
		}
		else if (only_contains_white_space_after_pipe(&input[i + 1]))
		{
			printf("\nLAST CHAR PIPE\n");
			return (FALSE);
		}
		if (i == 0)
		{
			printf("\nFIRST CHAR PIPE\n");
			return (FALSE);
		}
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
