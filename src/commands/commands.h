#ifndef COMMANDS_H
# define COMMANDS_H
# define WHITESSPACE_AND_QUOTES " 	\""
# define WHITESSPACE " \t"
# define N_FLAG "-n"
# define REDIRECTION_CHARS "<>|" 
# define SPECIALS "<>| \0" 

# include <defines.h>

/* I think space and NULL shouldn't be
in special chars, we should create a new enum for them */
typedef enum e_special_chars
{
	SPACE = ' ',
	NULL_TERMINATOR = '\0',
	PIPE = '|',
	LEFT_ANGLE = '<',
	RIGHT_ANGLE = '>'
}	t_special_chars;

typedef struct s_arg
{
	const char	*start;
	const char	*end;
}	t_arg;

typedef struct s_files
{
	int	out;
	int	in;
}	t_files;

typedef struct s_command
{
	t_command_code	code;
	t_arg			arg;
	t_files			files;
	int				arg_len;
	const char		*exe_path;
}	t_command;

typedef void	(*t_output_stdout)(const char *);

t_exit_code	exit_command(t_command command, t_output_stdout write_to_stdout);
t_exit_code	echo_command(t_command command_table, t_output_stdout output);
t_exit_code	pwd_command(t_command command, t_output_stdout output);
t_exit_code	export_command(t_command command, t_output_stdout output);
t_exit_code	unset_command(t_command command, t_output_stdout output);
t_exit_code	env_command(t_command command, t_output_stdout output);

#endif
