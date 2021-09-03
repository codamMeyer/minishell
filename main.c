#include <stdio.h>
#include <stdlib.h>
#include <libft.h>
#include <output/prompt.h>
#include <defines.h>
#include <parser/parser.h>
#include <env/environment.h>
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

static void setup_env(char *envp[])
{
	t_env *env;
	int i;

	env = get_environment();
	i = 0;
	while (envp[i] != NULL)
	{
		export(env, envp[i]);
		++i;
	}
	while (i < ENV_SIZE)
	{
		env[i].key = NULL;
		env[i].value = NULL;
		++i;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	
	setup_env(envp);
	run();
	return (0);
}
