#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>

# define WHITESSPACE_AND_QUOTES " 	\""

typedef struct s_check_quotes
{
	t_bool	opening;
	t_bool	closing;
}	t_check_quotes;

typedef enum e_special_chars
{
	SPACE = ' ',
	NULL_TERMINATOR = '\0'
}	t_special_chars;

void	exit_command(t_exit_code exit_code);

int		echo_command(const char **input);
char	**parse_echo(const char **input);
int		get_substr_len(const char *input);
t_bool	has_inverted_comma_set(const char *input, t_check_quotes *quotes);
char	**format_string_with_quotes(const char *str_w_quotes);
void	write_space_between_words(const char *next_string);

#endif
