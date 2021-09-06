#include <stdio.h>
#include <stdlib.h>
#include <output/prompt.h>
#include <parser/parser.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

/*
	added the line NULL check to listen for EOF
*/

static void	run(const char *env[])
{
	char	*line;
	char	buffer[4096];

	while (TRUE)
	{
		line = readline(display_prompt(&buffer[0]));
		if (line == NULL)
			exit(1);
		parse_input(line, env);
		free(line);
	}
}

int	main(const int argc, const char *argv[], const char *env[])
{
	(void)argc;
	(void)argv;
	run(env);
	return (0);
}
