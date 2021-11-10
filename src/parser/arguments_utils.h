#ifndef ARGUMENTS_UTILS_H
# define ARGUMENTS_UTILS_H
# include <commands/buffer.h>

void	populate_buffer_with_expanded_value(t_arg *arg, t_buffer *buffer);
void	copy_string_to_buffer(const char **str, t_buffer *buffer);
char	*get_substring(const char **str);
char	**split(char **splits, const char *str, int n_splits);
int		count_num_of_splits(char const *str);

#endif