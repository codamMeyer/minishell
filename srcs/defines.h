#ifndef DEFINES_H
# define DEFINES_H

# define TRUE 1
# define FALSE 0

typedef int	t_bool;

# define ECHO_STR "echo"

typedef enum e_command
{
	INVALID = -1,
	ECHO = 1
}			t_command;

#endif