#ifndef ECHO_UTILS_H
#define ECHO_UTILS_H
#include <defines.h>

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

int	get_substr_len(const char *input);
t_bool	has_inverted_comma_set(const char *input, t_check_quotes *quotes);
char	**format_string_with_quotes(const char *str_w_quotes);
void	write_space_between_words(const char *next_string);
t_bool	parse_n_flag(const char **input);

#endif