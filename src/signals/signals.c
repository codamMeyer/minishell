#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <defines.h>
#include <output/prompt.h>

static void	reprompt(int signal_code)
{
	if (signal_code == SIGINT)
	{
		ft_putendl_fd("", STDOUT_FILENO);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

static void	prep_repromt(int signal_code)
{
	(void)signal_code;
	ft_putstr_fd("\n", STDOUT_FILENO);
}

void	set_program_signals(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_quit(int signal_code)
{
	(void)signal_code;
	ft_putstr_fd("Quit: 3\n", 2);
}

void	set_child_signals(void)
{
	signal(SIGINT, prep_repromt);
	signal(SIGQUIT, handle_quit);
}
