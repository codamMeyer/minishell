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

int	*heredoc_sigint(void)
{
	static int sig_interupt = 0;

	return (&sig_interupt);
}

void	heredoc_signals(int code)
{
	(void)code;
	int *signal = heredoc_sigint();

	*signal = 666;
	rl_done = 1;
}

void	set_heredoc_signals(void)
{
	signal(SIGINT, heredoc_signals);
}

int event(void) {return 1;};

void	set_program_signals(void)
{
	signal(SIGINT, reprompt);
	signal(SIGQUIT, SIG_IGN);
	rl_event_hook = event;
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


// void	sigint_for_heredoc(int signal_code)
// {
// 	(void)signal_code;
// 	rl_reset_line_state();      // Resets the display state to a clean state
//     rl_cleanup_after_signal();  // Resets the terminal to the state before readline() was called
//     rl_replace_line("",0);      // Clears the current prompt
//     rl_crlf();                  // Moves the cursor to the next line
//     rl_redisplay();   
// 	// rl_done = 1;
// 	// reprompt(signal_code);
// }
