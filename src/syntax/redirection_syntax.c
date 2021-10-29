#include <libft.h>
#include <syntax/check_syntax.h>
#include <syntax/write_errors.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "redirection_syntax.h"
#include <stdio.h>

t_bool	is_redirection_char(const char c)
{
	return (c == LEFT_ANGLE || c == RIGHT_ANGLE);
}

int	get_redirect_token(const char *cursor)
{
	int	token;

	if (*cursor == PIPE)
		token = PIPE;
	else
		token = get_redirect_id(cursor);
	if (!is_valid_token(cursor, token))
		return (ERROR);
	return (token);
}

t_bool	is_valid_file_redirect(const char *input, int id)
{
	t_buffer	buffer;

	init_buffer(&buffer);
	if (id == ERROR)
		return (FALSE);
	while (is_redirection_char(*input))
		++input;
	skip_spaces(&input);
	if (is_redirection_char(*input))
	{
		append_error_token_to_buffer(input, buffer.buf);
		write_error(buffer.buf);
		return (FALSE);
	}
	get_file_name_and_length(&buffer, (char *)input, id);
	if (id == FT_TRUNCATE
		&& file_name_contains_only_digits(&buffer.buf[0], input))
		return (FALSE);
	return (TRUE);
}

/* 
	Expects a trimmed string
*/
t_bool	is_valid_redirection_syntax(const char *input)
{
	int	redirect_token;

	if (*input == PIPE)
	{
		handle_error(SYNTAX_ERROR, "syntax error near unexpected token `|'\n", NULL);
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
