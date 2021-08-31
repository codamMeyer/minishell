#include <stdio.h>
#include <stdlib.h>
#include <output/prompt.h>
#include <parser/parser.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	run(void)
{
	char	*line;
	char	buffer[4096];

	while (TRUE)
	{
		line = readline(display_prompt(&buffer[0]));
		parse_input(line);
		free(line);
	}
}

int	main(const int argc, const char *argv[], const char *env[])
{
	(void)argc;
	(void)argv;
	(void)env;
	run();
	return (0);
}
