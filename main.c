#include <stdio.h>
#include <stdlib.h>
#include "srcs/output/prompt.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "srcs/defines.h"
#include "srcs/parser/parser.h"

static void run()
{
	char *line;

	while(TRUE)
	{
		line = readline("BestShellEver: ");
		if (!parse_input(line))
			return ;
		free(line);
	}
}

int main(void)
{
	
	run();
	return (0);
}