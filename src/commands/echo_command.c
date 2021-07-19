#include "commands.h"
#include <stdio.h>
#include <unistd.h>
// only echo = \n
// if in inverted commas printf white space trim inverted commas though
// if no inverted commas remove trim all white space including between words


int	echo_command(const char **input)
{
	(void)input;
	// check if has ""
	// printf("%s\n", *input);
	write(1, NEW_LINE, 1);
	return (1);
}