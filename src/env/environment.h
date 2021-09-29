#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <commands/commands.h>
# include <commands/buffer.h>
# include <defines.h>
# define ENV_SIZE 2049

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

t_bool	export(t_env *env, const char *key_value_str);
void	unset(t_env *env, const char *key);
void	display_env(t_env *env, t_output_stdout output);
t_env	*find_variable(t_env *env, const char *key);
void	destroy_env(t_env *env, int size);
t_bool	copy_key_to_buffer(const char *key_value_str, t_buffer *buffer);
t_bool	copy_value_to_buffer(const char *key_value_str, t_buffer *buffer);
t_bool	set_key(t_env *env, char *key);
t_bool	set_value(t_env *env, char *key, char *value);
int		get_next_available_index(t_env *env);
char	*get_equal_sign_position(const char *key_value_str);
void	free_key_value_pair(t_env *env);
t_env	*get_environment(void);

#endif
