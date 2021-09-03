#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <defines.h>
# define ENV_SIZE 2049
# define EQUAL_SIGN '='

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

t_bool	export(t_env *env, const char *key_value_str);
void	unset(t_env *env, const char *key_name);
void	display(t_env *env);
char	*find(t_env *env, const char *key_name);
void	destroy(t_env *env, int size);
t_bool	copy_key_to_buffer(const char *key_value_str, char *buffer);
int		get_next_available_index(t_env *env);
char	*get_equal_sign_position(const char *key_value_str);
void	free_key_value_pair(t_env *env);
t_env	*get_environment(void);

#endif