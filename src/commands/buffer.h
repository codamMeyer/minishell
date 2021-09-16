#ifndef BUFFER_H
# define BUFFER_H
# define BUFFER_SIZE 4096
# include <commands/commands.h>

typedef struct s_buffer
{
	char	buf[BUFFER_SIZE];
	int		index;
}	t_buffer;

void	init_buffer(t_buffer *buffer);
t_arg	append_char_to_buffer(t_arg arg, t_buffer *buffer);
void	append_value_to_buffer(t_arg *echo_arg, t_buffer *buffer);

#endif