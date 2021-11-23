#include <syntax/check_syntax.h>
#include <syntax/redirection_syntax.h>
#include <syntax/write_errors.h>
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
	while (file[i])
	{
		if (!ft_isdigit(file[i]))
			return (FALSE);
		i++;
	}
	if (input[file_len] != SPACE_CHAR && input[file_len] != NULL_TERMINATOR)
	{
		handle_error(SYNTAX_ERROR, "syntax error near unexpected token `", \
					&file[file_len - 1]);
		write_to_stderr("'\n");
		return (TRUE);
	}
	return (FALSE);
}

t_bool	redirect_is_last_char(const char *str)
{
	if (*str)
		++str;
	skip_spaces(&str);
	if (*str == NULL_TERMINATOR)
	{
		write_error("newline");
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
		handle_error(SYNTAX_ERROR, "syntax error near unexpected token `|'\n", \
		 NULL);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	is_valid_token(const char *input, int redirect_id)
{
	int		i;
	char	buffer[BUFFER_SIZE];

	i = 0;
	while (input && input[i] && is_redirection_char(input[i]) && i < 3)
		i++;
	if (i > 2)
	{
		append_error_token_to_buffer(&input[i - 1], buffer);
		write_error(&buffer[0]);
		return (FALSE);
	}
	else if (i > 1 && !is_multi_angled_bracket(redirect_id))
	{
		append_error_token_to_buffer(&input[i], buffer);
		write_error(&buffer[0]);
		return (FALSE);
	}
	return (TRUE);
}
