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

t_bool	only_contains_white_space_after_redirect(const char *str)
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

t_bool	is_valid_eol(int index, int len, char last_char)
{
	return (index == len && (last_char == NULL_TERMINATOR
			|| ft_strchr(REDIRECTION_CHARS, last_char)));
}

/*
	Some checks are the same, like if a redirect char
	is followed by only spaces it's invalid
	Thinking of doing get_arg_len up to the first redirect char
	and then that as an index for calling a function
	in an array of function pointers 
	Might be over complex but hey!?
*/
t_bool	is_valid_redirection_syntax(const char *input)
{
	const int	len = ft_strlen(input);
	int			i;

	i = 0;
	while (input && input[i])
	{
		skip_spaces(&input);
		i += get_arg_len(&input[i], REDIRECTION_CHARS);
		if (is_valid_eol(i, len, input[i]))
			break ;
		else if (i == 0 && input[i] == PIPE)
			return (FALSE);
		while (input[i] && isspace(input[i + 1]))
			i++;
		if (only_contains_white_space_after_redirect(&input[i]))
			return (FALSE);
		else if (input[i + 1] == PIPE)
			return (FALSE);
		++i;
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
