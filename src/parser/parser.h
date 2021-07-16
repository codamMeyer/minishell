#ifndef PARSER_H
# define PARSER_H

# include <defines.h>

t_bool		parse_input(const char *input);
t_command	parse_command(const char **input);
void		advance_pointer(const char **input, const char *command_str);
void		skip_spaces(const char **input);

#endif