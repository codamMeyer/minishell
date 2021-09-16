#ifndef PARSE_REDIRECTION_H
# define PARSE_REDIRECTION_H

# include <commands/commands.h>

void	check_cmd_str_validity(char *cmd_str);
t_files	get_redirection(char **input, const int string_to_parse_len);
int		count_consecutive_spaces(char *str);
int		get_file_name_and_length(char *buffer, char *input);
int		open_file(char *file_name_ptr, t_files *files, int redirection_id);
void	replace_redirection_w_space(char **input, int len, int start);

#endif