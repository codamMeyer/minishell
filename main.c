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

static void	add_key_and_value_from_env(char *env_str_pair)
{
	char		*value;
	t_buffer	key;

	init_buffer(&key);
	copy_key_to_buffer(env_str_pair, &key);
	set_key(get_environment(), key.buf);
	value = get_equal_sign_position(env_str_pair) + 1;
	if (ft_strncmp(key.buf, "SHLVL", 6) == 0)
	{
		value = ft_itoa(ft_atoi(value) + 1);
		set_value(get_environment(), key.buf, value);
		free(value);
	}
	else
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

static char	*get_line(void)
{
	char	*line;
	char	buffer[BUFFER_SIZE];

	line = readline(display_prompt(&buffer[0]));
	if (!line)
	{
		ft_putstr_fd("exit", STDERR_FILENO);
		exit(SUCCESS);
	}
	if (*line)
		add_history(line);
	return (line);
}

static void	run(void)
{
	char	*line;

	while (TRUE)
	{
		set_program_signals();
		line = get_line();
		if (is_valid_syntax(line))
			parse_input(line);
		free(line);
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
