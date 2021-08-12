#ifndef DEFINES_H
# define DEFINES_H

# define NEW_LINE "\n"
# define DOUBLE_QUOTES '"'

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_command_code
{
	ECHO = 0,
	EXIT,
	PWD,
	EMPTY_LINE,
	INVALID,
	LAST,
}			t_command_code;

typedef enum e_exit_code
{
	SUCCESS = 0,
	ERROR = 1
}	t_exit_code;

#endif