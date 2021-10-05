#include <syntax/check_syntax.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "redirection_syntax.h"
#include <stdio.h>

int	get_redirect_token(const char *cursor)
{
	if (is_invalid_token(cursor))
		return (ERROR);
	if (*cursor == PIPE)
		return (PIPE);
	else
		return (get_redirect_id(cursor));
}

t_bool	is_redirection_char(const char c)
{
	return (c == LEFT_ANGLE || c == RIGHT_ANGLE);
}

t_bool	is_valid_file_redirect(const char *input, int id)
{
	char	buffer[BUFFER_SIZE];
	int		len;

	if (id == ERROR)
		return (FALSE);
	while (is_redirection_char(*input))
		++input;
	skip_spaces(&input);
	if (is_redirection_char(*input))
		return (FALSE);
	len = get_file_name_and_length(&buffer[0], (char *)input);
	if (id == FT_TRUNCATE && file_name_contains_only_digits(buffer, input))
		return (FALSE);
	return (TRUE);
}

/* REMEMBER TO REMOVE UNNECESARY SKIP SPACES */
/* is_valid_redirection_syntax input will always be a trimmed string */
/*  */
t_bool	is_valid_redirection_syntax(const char *input)
{
	int	redirect_token;

	if (*input == PIPE)
	{
		write_to_stderr("syntax error near unexpected token `|'\n");
		return (FALSE);
	}
	while (input && *input)
	{
		input += get_set_index(input, REDIRECTION_CHARS);
		redirect_token = get_redirect_token(input);
		if (*input == NULL_TERMINATOR)
			break ;
		if (redirect_is_last_char(input))
			return (FALSE);
		else if (redirect_token == PIPE && is_double_pipe(input))
			return (FALSE);
		else if (!is_valid_file_redirect(input, redirect_token))
			return (FALSE);
		++input;
	}
	return (TRUE);
}
