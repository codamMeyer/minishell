#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include <defines.h>
# include <commands/commands.h>

t_bool				parse_n_flag(t_arg *input);
void				write_to_stdout(const char *string_to_write);
void				write_to_stderr(const char *string_to_write);
void				trim_extra_spaces_between_words(t_arg *arg, t_buffer *buffer);

#endif
