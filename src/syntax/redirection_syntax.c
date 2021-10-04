#include <syntax/check_syntax.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <parser/parse_redirection.h>
#include <libft.h>
#include <stdio.h>

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

t_bool	is_invalid_token(const char *input)
{
	if (ft_strncmp(input, "<<<", 3) == SUCCESS)
		return (TRUE);
	else if (ft_strncmp(input, ">>>", 3) == SUCCESS)
		return (TRUE);
	return (FALSE);
}

int	get_redirect_token(const char *cursor)
{
	if (is_invalid_token(cursor))
		return (ERROR);
	if (*cursor == PIPE)
		return (PIPE);
	else
		return (get_redirect_id(cursor));
}


/* REMEMBER TO REMOVE UNNECESARY SKIP SPACES */
/* is_valid_redirection_syntax input will always be a trimmed string */
/*  */
t_bool	is_valid_redirection_syntax(const char *input)
{
	int redirect_token;

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
		if (redirect_token == INVALID)
			printf("ERROROOOOROOROROROOROROR\n");
		if (redirect_is_last_char(input))
			return (FALSE);
		else if (redirect_token == PIPE && is_double_pipe(input))
			return (FALSE);
		// else
		// 	check_file_token_syntax(input, redirect_token);
		++input;
	}
	return (TRUE);
}
