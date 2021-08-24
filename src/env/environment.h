#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <defines.h>
# define ENV_SIZE 50

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

#endif