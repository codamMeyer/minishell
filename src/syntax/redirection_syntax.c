#include <libft.h>
#include <syntax/check_syntax.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include "redirection_syntax.h"
#include <stdio.h>


/*
	receives a pointer to the first faulty char
	copies up to two angled brackets
*/
void	append_error_token_to_buffer(const char *input, char *buffer)
{
	int	i;

	i = 0;
	skip_spaces(&input);
	while (input && i < 2 && input[i] && is_redirection_char(input[i]))
		++i;
	ft_strlcpy(buffer, input, i + 1);
}

void	write_error(const char *error_token_pointer)
{
	write_to_stderr("syntax error near unexpected token `");
	write_to_stderr(error_token_pointer);
	write_to_stderr("'\n");
}

int	get_redirect_token(const char *cursor)
{
	int	id;

	if (*cursor == PIPE)
		id = PIPE;
	else
		id = get_redirect_id(cursor);
	if (id == INVALID || !is_valid_token(cursor, id))
		return (ERROR);
	return (id);
}

t_bool	is_redirection_char(const char c)
{
	return (c == LEFT_ANGLE || c == RIGHT_ANGLE);
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
	get_file_name_and_length(&buffer, (char *)input);
	if (id == FT_TRUNCATE && file_name_contains_only_digits(&buffer.buf[0], input))
		return (FALSE);
	return (TRUE);
}

/* 
	is_valid_redirection_syntax expects a trimmed string
*/
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
