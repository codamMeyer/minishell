#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>

# define WHITESSPACE_AND_QUOTES " 	\""
# define WHITESSPACE " \t"
# define N_FLAG "-n"

typedef enum e_special_chars
{
	SPACE = ' ',
	NULL_TERMINATOR = '\0'
}	t_special_chars;

typedef void (*t_output_stdout)(const char **);

void	exit_command(t_exit_code exit_code);
int		echo_command(const char **input, t_output_stdout output);

#endif
