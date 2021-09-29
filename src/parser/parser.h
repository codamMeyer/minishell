#ifndef PARSER_H
# define PARSER_H
# include <commands/commands.h>
# include <defines.h>
# include <env/environment.h>

t_bool			parse_input(const char *input, char *env[]);
void			advance_pointer(const char **input, const char *parsed_str);
void			skip_spaces(const char **input);
int				populate_commands_table(const char *input, \
									t_command commands_table[]);

#endif
