#ifndef EXPORT_UTILS_H
# define EXPORT_UTILS_H
# include <defines.h>
# include <env/environment.h>

t_bool		is_valid_key(char *key, int key_len);
t_bool		add_variable_to_tmp_env(t_env *tmp_env, char **key_value_str);
int			add_variables_to_tmp_env(t_env *tmp_env, char **arguments);
t_exit_code	add_variables_to_env(t_env *env, \
									t_env *tmp_env, \
									int variables_count);
#endif