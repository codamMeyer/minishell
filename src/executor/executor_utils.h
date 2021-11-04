#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

# define SIGNAL_INCREMENT 128

# include <commands/commands.h>
# include <executor/redirection.h>

t_exit_code	wait_for_all_processes(int num_of_processes, int *pids);
void		handle_errors(int error_code, const char *location);
void		execute_system_command(const t_command *command, char *env[]);
int			create_new_process(t_multi_pipes *pipes,
				int current_process, int num_of_process);

#endif
