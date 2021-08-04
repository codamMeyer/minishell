#ifndef ECHO_UTILS_H
#define ECHO_UTILS_H
#include <defines.h>

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

int	get_substr_len(const char *input);
t_bool	has_double_quotes_set(const char *input, t_check_quotes *quotes);
char	**format_string_with_quotes(const char *str_w_quotes);
void	write_space_between_words(const char *next_string);
t_bool	parse_n_flag(const char **input);
void	write_echo_args(const char **strings_to_write);
void	echo_stdout(const char *string_to_write, int len);

#endif