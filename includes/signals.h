#ifndef SIGNALS_H
# define SIGNALS_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

void	activate_signal_handler(void);
void	sig_handler(int sig);
void	ignore_signals(void);
void	here_doc_sig(int sig);

#endif
