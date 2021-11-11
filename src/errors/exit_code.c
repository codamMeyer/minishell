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
	const int	exit_code_len = ft_strlen(exit_code_string);
	const char	*ptr = exit_code_string;

	ft_strlcpy(&buffer->buf[buffer->index],
		exit_code_string, exit_code_len + 1);
	buffer->index += exit_code_len;
	*start += 2;
	free((void *)ptr);
}
