#include <libft.h>
#include <parser/parser.h>
#include <syntax/redirection_syntax.h>
#include <output/write_to_std.h>

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
	handle_error(SYNTAX_ERROR, "syntax error near unexpected token `", \
				error_token_pointer);
	write_to_stderr("'\n");
}
