#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <defines.h>
# define ENV_SIZE 100

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

t_bool	export_env_set(char *key_value_str, t_env *env);
void	destro_env_set(t_env *env);

#endif