#ifndef SORT_ENV_H
# define SORT_ENV_H
# include <env/environment.h>

int		populate_env_index_buffer(int buffer[]);
int		sort_env(const t_env *env, int buffer[]);
void	display_sorted_env(void);

#endif