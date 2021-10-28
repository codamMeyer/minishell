#ifndef DEFINES_H
# define DEFINES_H
# define NEW_LINE "\n"
# define DOUBLE_QUOTES '"'
# define SINGLE_QUOTES 39
# define MAX_CMDS_PER_LINE 4096
# define BUFFER_SIZE 4096

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_command_code
{
	EMPTY_LINE,
	ECHO,
	EXIT,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	CD,
	INVALID,
	SYSTEM,
	LAST,
}			t_command_code;

#endif
