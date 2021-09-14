#ifndef PARSE_REDIRECTION_H
# define PARSE_REDIRECTION_H

# include <commands/commands.h>

// void	init_files(t_files *files);
// void	get_in_out_file(const char **input_ptr, const char id, t_files *files);
void	skip_redirection(const char **input_ptr);
void	check_cmd_str_validity(char *cmd_str);

#endif