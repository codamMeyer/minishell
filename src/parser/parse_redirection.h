#ifndef PARSE_REDIRECTION_H
# define PARSE_REDIRECTION_H

# include <commands/commands.h>

// void	init_files(t_files *files);
// void	get_in_out_file(const char **input_ptr, const char id, t_files *files);
void	skip_redirection(const char **input_ptr);
void	check_cmd_str_validity(char *cmd_str);
t_files	get_redirection(char **input);
int		get_files_descriptors(char *input, t_files *fd, int redirection_id);
int		count_consecutive_spaces(char *str);
int		get_file_name_and_length(char *buffer, char *input);
int		open_infile(char *file_name_ptr, int *in_file);
void	replace_redirection_w_whitespace(char **input, int len, int start);

#endif