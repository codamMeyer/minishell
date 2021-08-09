#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include <defines.h>

t_bool				parse_n_flag(const char **input);
void				echo_stdout(const char *string_to_write, int len);
void				trim_extra_spaces_between_words(const char **input,
						char *stdout_buffer,
						int *buffer_index);

#endif