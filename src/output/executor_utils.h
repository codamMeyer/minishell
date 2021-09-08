#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H
# define DEFAULT_WAIT_ID -1
# include <commands/commands.h>
# include <output/redirection.h>

void	wait_for_all_processes(int num_of_processes);
void	handle_errors(int error_code, char *location);
int		execute_command(const char *path, char *argv[], char *env[]);
void	execute_system_command(const t_command *command, char *env[]);
int		create_new_process(t_multi_pipes *pipes);

#endif
