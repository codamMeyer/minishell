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
void	append_char_to_buffer(const char **start, t_buffer *buffer);
void	append_env_value_to_buffer(const char **start, \
									 t_buffer \
									 *buffer, \
									 t_bool trimmed);
void	append_quoted_string_to_buffer(const char **start, t_buffer *buffer);
void	append_expanded_input_to_buffer(t_arg *arg, t_buffer *buffer);

#endif