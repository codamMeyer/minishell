#ifndef COMMANDS_H
# define COMMANDS_H
# include <defines.h>
# include <errors/errors.h>
# define WHITESSPACE_AND_QUOTES " 	\""
# define WHITESSPACE " \t\v"
# define N_FLAG "-n"
# define REDIRECTION_CHARS "<>|" 
# define ALL_TERMINATORS "<>| \0" 

typedef enum e_special_chars
{
	SPACE_CHAR = ' ',
	NULL_TERMINATOR = '\0',
	PIPE = '|',
	LEFT_ANGLE = '<',
	RIGHT_ANGLE = '>',
	VARIABLE_TOKEN = '$',
	EQUAL_SIGN = '=',
}	t_special_chars;

typedef struct s_files
{
	int	out;
	int	in;
}	t_files;

typedef struct s_command
{
	t_command_code	code;
	t_files			files;
	char			**arguments;
	const char		*exe_path;
}	t_command;

typedef void	(*t_output_stdout)(const char *);

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout);
t_exit_code	echo_command(t_command command_table, t_output_stdout output);
t_exit_code	pwd_command(t_command command, t_output_stdout output);
t_exit_code	export_command(t_command command, t_output_stdout output);
t_exit_code	unset_command(t_command command, t_output_stdout output);
t_exit_code	env_command(t_command command, t_output_stdout output);
t_exit_code	cd_command(t_command command, t_output_stdout output);

#endif
