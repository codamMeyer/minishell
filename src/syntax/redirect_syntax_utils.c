#include <syntax/check_syntax.h>
#include <syntax/redirection_syntax.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <libft.h>
#include <stdio.h>

t_bool	file_name_contains_only_digits(const char *file, const char *input)
{
	const int	file_len = ft_strlen(file);
	int			i;

	i = 0;
	while (file[i] && ft_isdigit(file[i]))
		i++;
	if (file_len == i && input[file_len] && input[file_len] != SPACE_CHAR)
	{
		printf("syntax error near unexpected token\
					`%c'\n", file[file_len - 1]);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	redirect_is_last_char(const char *str)
{
	char	token_buf[2];

	token_buf[0] = *str;
	token_buf[1] = '\0';
	if (*str)
		++str;
	skip_spaces(&str);
	if (*str == NULL_TERMINATOR)
	{
		write_to_stderr("syntax error near unexpected token `");
		write_to_stderr(token_buf);
		write_to_stderr("'\n");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_valid_eol(char last_char)
{
	return (last_char == NULL_TERMINATOR
		|| !ft_strchr(REDIRECTION_CHARS, last_char));
}

t_bool	is_double_pipe(const char *str)
{
	if (*str == PIPE)
		++str;
	skip_spaces(&str);
	if (*str == PIPE)
	{
		write_to_stderr("syntax error near unexpected token `|'\n");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_valid_token(const char *input, int redirect_id)
{
	int	i;

	i = 0;
	while (input && input[i] && is_redirection_char(input[i]))
		i++;
	if (i > 2)
		return (FALSE);
	else if (i > 1 && !is_multi_angled_bracket(redirect_id))
		return (FALSE);
	return (TRUE);
}
