#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <output/prompt.h>
#include <defines.h>
#include <parser/parser.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	run(void)
{
	char	*line;

	while (TRUE)
	{
		line = readline("BestShellEver: ");
		parse_input(line);
		free(line);
	}
}

int	main(int argc, const char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;
	run();
	return (0);
}
