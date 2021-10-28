#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <env/environment.h>
#include <libft.h>
#include <parser/parser.h>
#include <output/prompt.h>
#include <syntax/check_syntax.h>
#include <errors/errors.h>
#include <signals/signals.h>
#include <errors/errors.h>

static void	add_key_and_value_from_env(char *env_str_pair)
{
	char		*value;
	t_buffer	key;

	init_buffer(&key);
	copy_key_to_buffer(env_str_pair, &key);
	set_key(get_environment(), key.buf);
	value = get_equal_sign_position(env_str_pair) + 1;
	set_value(get_environment(), key.buf, value);
}

static void	setup_env(char *envp[])
{
	int			i;

	i = 0;
	while (envp[i] != NULL)
	{
		add_key_and_value_from_env(envp[i]);
		++i;
	}
}

static char	*get_trimmed_line(void)
{
	char	*line;
	char	*trimmed_line;
	char	buffer[BUFFER_SIZE];

	line = readline(display_prompt(&buffer[0]));
	if (!line)
	{
		ft_putstr_fd("exit", STDERR_FILENO);
		exit(0);
	}
	if (*line)
		add_history(line);
	trimmed_line = ft_strtrim(line, WHITESSPACE);
	free(line);
	return (trimmed_line);
}

static void	run(char *env[])
{
	char	*line;

	while (TRUE)
	{
		set_program_signals();
		line = get_trimmed_line();
		set_return_code(0);
		if (!line)
			handle_error(MALLOC_ERROR, NULL);
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
