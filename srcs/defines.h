#ifndef DEFINES_H
# define DEFINES_H

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_command
{
	ECHO = 0,
	EMPTY_LINE,
	INVALID,
	LAST,
}			t_command;

#endif