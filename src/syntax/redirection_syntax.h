#ifndef REDIRECTION_SYNTAX_H
# define REDIRECTION_SYNTAX_H

# include <defines.h>

t_bool	is_valid_angled_brackets_syntax(const char *input);
t_bool	redirect_is_last_char(const char *str);
t_bool	is_valid_eol(char last_char);
t_bool	is_double_pipe(const char *str);
t_bool	is_valid_redirection_syntax(const char *input);

#endif