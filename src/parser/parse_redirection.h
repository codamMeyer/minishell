#ifndef PARSE_REDIRECTION_H
# define PARSE_REDIRECTION_H

# include <commands/commands.h>

// void	init_files(t_files *files);
// void	get_in_out_file(const char **input_ptr, const char id, t_files *files);
void	skip_redirection(const char **input_ptr);
void	check_cmd_str_validity(char *cmd_str);
t_files	get_redirection(char **input);
int		count_consecutive_spaces(char *str);
int		get_file_name_and_length(char *buffer, char *input);

#endif