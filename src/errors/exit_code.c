#include <errors/exit_code.h>
#include <commands/buffer.h>
#include <stdlib.h>
#include <libft.h>

t_exit_code	*get_exit_code(void)
{
	static t_exit_code	code = 0;

	return (&code);
}

t_exit_code	set_exit_code(t_exit_code new_code)
{
	t_exit_code	*code;

	code = get_exit_code();
	*code = new_code;
	return (*code);
}

void	append_exit_code_to_buffer(const char **start, t_buffer *buffer)
{
	const char	*exit_code_string = ft_itoa((int)*get_exit_code());
	const char	*ptr = exit_code_string;

	while (*exit_code_string)
		append_char_to_buffer(&exit_code_string, buffer);
	*start += 2;
	free((void *)ptr);
}
