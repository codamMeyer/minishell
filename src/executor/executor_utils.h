/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor_utils.h                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 22:11:37 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/09/09 16:27:39 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H
# define DEFAULT_WAIT_ID -1
# include <commands/commands.h>
# include <executor/redirection.h>

void	wait_for_all_processes(int num_of_processes);
void	handle_errors(int error_code, char *location);
int		execute_command(const char *path, char *argv[], char *env[]);
void	execute_system_command(const t_command *command, char *env[]);
int		create_new_process(t_multi_pipes *pipes);

#endif
