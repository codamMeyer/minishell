#include <syntax/check_syntax.h>
#include <commands/commands.h>
#include <output/write_to_std.h>
#include <parser/command_table.h>
#include <executor/executor_utils.h>
#include <parser/parser.h>
#include <libft.h>

t_bool	is_valid_angled_brackets_syntax(const char *input)
{
	(void)input;
	return (TRUE);
}

t_bool	redirect_is_last_char(const char *str)
{
	if (*str)
		++str;
	skip_spaces(&str);
	if (*str == NULL_TERMINATOR)
	{
		write_to_stderr("syntax error near unexpected token `|'\n");
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

/*
	Some checks are the same, like if a redirect char
	is followed by only spaces it's invalid
	Thinking of doing get_set_index up to the first redirect char
	and then that as an index for calling a function
	in an array of function pointers 
	Might be over complex but hey!?
	REMEMBER TO REMOVE UNNECESARY SKIP SPACES
*/

/* is_valid_redirection_syntax input will always be a trimmed string */
t_bool	is_valid_redirection_syntax(const char *input)
{
	if (*input == PIPE)
	{
		write_to_stderr("syntax error near unexpected token `|'");
		return (FALSE);
	}
	while (input && *input)
	{
		input += get_set_index(input, "|");
		if (*input == NULL_TERMINATOR)
			break ;
		if (redirect_is_last_char(input) || is_double_pipe(input))
			return (FALSE);
		++input;
	}
	return (TRUE);
}
