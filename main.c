#include <stdio.h>
#include <stdlib.h>
#include <output/prompt.h>
#include <parser/parser.h>
#include <env/environment.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <syntax/check_syntax.h>
#include <libft.h>

static void	setup_env(char *envp[])
{
	t_env	*env;
	int		i;

	env = get_environment();
	i = 0;
	while (envp[i] != NULL)
	{
		export(env, envp[i]);
		++i;
	}
}

static char	*get_trimmed_line(void)
{
	char *line;
	char *trimmed_line;
	char	buffer[4096];

	line = readline(display_prompt(&buffer[0]));
	if (!line)
		exit(0);
	trimmed_line = ft_strtrim(line, WHITESSPACE);
	free(line);
	return (trimmed_line);
}

static void	run(char *env[])
{
	char	*line;

	while (TRUE)
	{
		line = get_trimmed_line();
		if (!line)
			printf("Allocation error\n");
		if (is_valid_syntax(line))
			parse_input(line, env);
		free(line);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	(void)argv;
	(void)argc;
	setup_env(envp);
	run(envp);
	return (0);
}
