#include <commands/buffer.h>
#include <libft.h>

void	init_buffer(t_buffer *buffer)
{
	ft_bzero(&buffer->buf[0], BUFFER_SIZE);
	buffer->index = 0;
}
