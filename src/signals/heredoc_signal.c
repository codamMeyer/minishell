#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <defines.h>
#include <output/prompt.h>
#include <signals/signals.h>

int	*heredoc_sigint(void)
{
	static int	sig_interupt = 0;

	return (&sig_interupt);
}

static void	heredoc_signals(int code)
{
	int	*signal;

	(void)code;
	signal = heredoc_sigint();
	*signal = 667;
	rl_done = 1;
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signals);
}

int	reset_rl_event(void)
{
	return (1);
}
