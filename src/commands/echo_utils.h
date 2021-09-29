#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include <defines.h>
# include <commands/commands.h>
# include <commands/buffer.h>

t_bool	parse_n_flag(t_arg *input);
void	trim_extra_spaces_between_words(t_arg *arg, t_buffer *buffer);

#endif
