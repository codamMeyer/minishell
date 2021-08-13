#ifndef PARSER_H
# define PARSER_H

# include <defines.h>
# include <commands/commands.h>

t_bool			parse_input(const char *input);
t_command_code	get_command_code(const char **input);
void			advance_pointer(const char **input, const char *parsed_str);
void			skip_spaces(const char **input);
t_command		*get_commands(const char **input);
t_bool          is_between_quotes(const char *input, int pipe_index);


#endif