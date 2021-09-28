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

t_bool	redirect_is_last_char(const char *str)
{
	if (*str)
		++str;
	skip_spaces(&str);
	return (*str == NULL_TERMINATOR);
}

t_bool	is_valid_eol(char last_char)
{
	return (last_char == NULL_TERMINATOR 
			|| !ft_strchr(REDIRECTION_CHARS, last_char));
}

t_bool is_double_pipe(const char *str)
{
	if (*str == PIPE)
		++str;
	skip_spaces(&str);
	return (*str == PIPE);
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
t_bool	is_valid_redirection_syntax(const char *input)
{
	if (*input == PIPE)
		return (FALSE);
	while (input && *input)
	{
		skip_spaces(&input);
		input += get_set_index(input, "|");
		if (*input == NULL_TERMINATOR)
			break ;
		if (redirect_is_last_char(input) || is_double_pipe(input))
			return (FALSE);
		++input;
	}
	return (TRUE);
}

/*
	for testing purposes this returns something.
	In the end it will call the error checking function
	that will also exit the current process
*/
t_bool	is_valid_syntax(const char *input)
{
	if (!is_valid_redirection_syntax(input))
		return (FALSE);
	else if (!is_valid_angled_brackets_syntax(input))
		return (FALSE);
	return (TRUE);
}
