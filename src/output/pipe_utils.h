#ifndef PIPE_UTILS_H
# define PIPE_UTILS_H

# include <commands/commands.h>
# include <output/redirection.h>

void	wait_for_all_processes(int num_of_processes);
void	handle_errors(int error_code, char *location);
int		execute_command(const char *path, char *argv[], const char *env[]);
void	execute_commands(const t_command *command, const char *env[]);
int		create_new_process(t_multi_pipes *pipes);

#endif
