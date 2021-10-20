#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <libft.h>
#include <output/prompt.h>


static void	reprompt(int signal_code)
{
	(void)signal_code;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0); // replaces previous command line ex "/Users/rmeiboom/Documents/minishell -► cat" is replaced with empty_line
	rl_redisplay(); // looks
}

void	set_signals_before_processes(void)
{
	signal(SIGINT, reprompt);
	// signal(SIGQUIT, void);
}

static void	reprompt_during_processes(int signal_code)
{
	(void)signal_code;
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0); // replaces previous command line ex "/Users/rmeiboom/Documents/minishell -► cat" is replaced with empty_line
	rl_set_prompt("");
	rl_redisplay(); // looks
}

void	set_signals_during_processes(void)
{
	signal(SIGINT, reprompt_during_processes);
	// signal(SIGQUIT, void);
}
