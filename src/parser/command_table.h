#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include <commands/commands.h>
# include <defines.h>

t_command_code	get_command_code(const char **input, t_command *command);
t_bool			is_between_quotes(const char *input, int reserved_char_index);
int				get_arg_len(const char *start, const char *set);
int				get_cmd_len(const char *input);
t_bool			is_system_command(const char *input, t_command *command);
char			*get_redirection_position(const char *set, char *str_to_check);

#endif
