#ifndef COMMAND_TABLE_H
# define COMMAND_TABLE_H
# include <defines.h>

t_command_code	get_command_code(const char **input);
t_bool			is_between_quotes(const char *input, int reserved_char_index);
int				get_arg_len(const char *start);

#endif