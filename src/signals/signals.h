#ifndef SIGNALS_H
# define SIGNALS_H

void	set_program_signals(void);
void	set_child_signals(void);
void	set_parent_signals(void);
void	set_heredoc_signals(void);
int     *heredoc_sigint(void);

#endif