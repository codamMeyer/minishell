#ifndef CHECK_SYNTAX_H
# define CHECK_SYNTAX_H

# include <defines.h>

t_bool	is_valid_angled_brackets_syntax(const char *input);
t_bool	isvalid_redirection_syntax(const char *input);
t_bool	is_valid_syntax(const char *input);

#endif