#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include <commands/buffer.h>
# include <commands/commands.h>
# include <defines.h>

t_command_code	get_command_code(const char **input, t_command *command);
t_bool			is_between_quotes(const char *input, int reserved_char_index);
int				get_set_index(const char *start, const char *set);
t_command		*expand_arg_content(t_command *command, t_buffer *buffer);
t_bool			is_system_command(const char *input, t_command *command);
char			*get_set_position(const char *set, char *str_to_check);
void			cleanup_command_table(t_command *command_table, \
									int num_commands);

#endif
