#ifndef REDIRECTION_SYNTAX_H
# define REDIRECTION_SYNTAX_H

# include <defines.h>

t_bool	is_valid_angled_brackets_syntax(const char *input);
t_bool	redirect_is_last_char(const char *str);
t_bool	is_valid_eol(char last_char);
t_bool	is_double_pipe(const char *str);
t_bool	is_valid_redirection_syntax(const char *input);
t_bool	file_name_contains_only_digits(const char *file, const char *input);
t_bool	is_valid_token(const char *input, int redirect_id);
t_bool	is_redirection_char(const char c);
void	write_error(const char *error_tokens);
void	append_error_token_to_buffer(const char *input, char *buffer);

#endif