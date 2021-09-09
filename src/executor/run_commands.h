/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   run_commands.h                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/07 22:11:55 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/09/09 16:26:56 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUN_COMMANDS_H
# define RUN_COMMANDS_H
# define FIRST_PROCESS 0
# define CHILD_PROCESS 0
# define SYS_ERROR -1
# define MAX_CMDS_PER_LINE 100

# include <commands/commands.h>
# include "redirection.h"

int		run_pipes(const char *env[]);
int		run_commands(t_command commands[],
			int num_of_commands, char *env[]);
void	handle_errors(int error_code, char *location);
void	create_table(t_command commands[], char *arg, char *path);

#endif