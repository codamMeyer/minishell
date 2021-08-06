#ifndef ECHO_UTILS_H
# define ECHO_UTILS_H
# include <defines.h>

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

typedef struct s_quotes_position
{
	const char	*start;
	const char	*end;
}	t_quotes_position;

t_quotes_position	get_quotes_positions(const char *input);
t_bool				parse_n_flag(const char **input);
void				echo_stdout(const char *string_to_write, int len);
void				trim_extra_spaces_between_words(const char **input,
						char *stdout_buffer,
						int *buffer_index);
t_bool				is_double_quote(char c);

#endif