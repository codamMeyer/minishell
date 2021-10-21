#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <defines.h>
#include <output/prompt.h>

static void	reprompt(int signal_code)
{
	(void)signal_code;
	if (signal_code == SIGINT)
	{
		ft_putendl_fd("", STDERR_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	reprompt2(int signal_code)
{
	(void)signal_code;
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	set_program_signals(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	set_child_signals(void)
{
	signal(SIGINT, reprompt2);
	signal(SIGQUIT, SIG_DFL);
}

void	set_parent_signals(void)
{
	signal(SIGINT, reprompt2);
}
