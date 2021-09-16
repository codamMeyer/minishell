#include <commands/buffer.h>
#include <libft.h>
#include <env/environment.h>
#include <env/env_utils.h>

void	init_buffer(t_buffer *buffer)
{
	ft_bzero(&buffer->buf[0], BUFFER_SIZE);
	buffer->index = 0;
}

t_arg	append_char_to_buffer(t_arg arg, t_buffer *buffer)
{
	buffer->buf[buffer->index] = *arg.start;
	++(buffer->index);
	++(arg.start);
	return (arg);
}

void	append_value_to_buffer(t_arg *echo_arg, t_buffer *buffer)
{
	t_env	*var;
	int		key_len;
	int		value_len;

	++(echo_arg->start);
	value_len = 0;
	key_len = get_key_len(echo_arg->start);
	var = find_variable(get_environment(), echo_arg->start);
	if (var)
	{
		value_len = ft_strlen(var->value);
		ft_strlcpy(&buffer->buf[buffer->index], var->value, value_len + 1);
	}
	echo_arg->start = echo_arg->start + key_len;
	buffer->index += value_len;
}
