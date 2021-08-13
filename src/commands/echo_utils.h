#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include <defines.h>

t_bool				parse_n_flag(t_arg *input);
void				write_to_stdout(const char *string_to_write);
void				trim_extra_spaces_between_words(const char **input,
						char *stdout_buffer,
						int *buffer_index);

#endif