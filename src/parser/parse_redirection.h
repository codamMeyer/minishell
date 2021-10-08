#ifndef PARSE_REDIRECTION_H
# define PARSE_REDIRECTION_H

# define INVALID_FD -1
# define FT_APPEND O_APPEND
# define FT_TRUNCATE O_TRUNC
# define HERE_DOC 666
# define FILE_RIGHTS 0664
# define TMP_FILE_PATH "/tmp/minishell"
# define DIAMOND_BRACKETS 777

# include <commands/commands.h>
# include <commands/buffer.h>

t_files	get_redirection(char **input, const int string_to_parse_len);
int		count_consecutive_spaces(const char *str);
int		get_file_name_and_length(t_buffer *buffer, char *input);
int		open_file(char *file_name_ptr, t_files *files, int redirection_id);
void	open_infile(const char *file, int *in_file);
void	open_outfile(const char *file, int *out_file, int out_mode);
void	replace_redirection_w_space(char **input, int len, int start);
int		get_redirect_id(const char *cursor);
t_bool	is_multi_angled_bracket(const int redirection_id);

#endif