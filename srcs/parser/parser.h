#ifndef PARSER_H
# define PARSER_H

# include "../defines.h"

t_bool		parse_input(const char *input);
t_command	parse_command(const char **input);

#endif