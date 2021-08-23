#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <defines.h>
# define ENV_SIZE 50

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

t_bool	export_env(char *key_value_str, t_env *env);
void	unset_env(char *key_name, t_env *env);
void	display_env(t_env *env);
char	*find_in_env(char *key_name, t_env *env);
void	destroy_env(t_env env[], int size);

#endif