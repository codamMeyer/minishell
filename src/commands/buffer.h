#ifndef BUFFER_H
# define BUFFER_H
# define BUFFER_SIZE 4096

typedef struct s_buffer
{
	char	buf[BUFFER_SIZE];
	int		index;
}	t_buffer;

void	init_buffer(t_buffer *buffer);

#endif