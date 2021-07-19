#ifndef DEFINES_H
# define DEFINES_H

# define NEW_LINE "\n"
# define INVERTED_COMMA '\"'
# define SPACES_AND_TABS " 	"

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef enum e_command
{
	ECHO = 0,
	EXIT,
	EMPTY_LINE,
	INVALID,
	LAST,
}			t_command;

typedef enum e_exit_code
{
	SUCCESS = 0
}	t_exit_code;

#endif