#ifndef ENV_UTILS_H
# define ENV_UTILS_H
# include <defines.h>

t_bool	is_valid_key_char(char c);
int		get_key_len(const char *key);
t_bool	is_env_variable(const char *str);

#endif