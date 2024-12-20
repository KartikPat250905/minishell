#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "gc_alloc.h"
# include "lexer.h"
# include "signals.h"
//# include "parsing.h"
# include "builtins.h"
# include "env.h"
#include <termios.h>
//# include "execution.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token_stack t_token_stack;

typedef struct s_info
{
	bool 	debug;
	bool	flag;
	t_token_stack	*tokens;
	t_env	*env; //head of a linked list
	int		exit_status;
	char	**envp; //move here //array //because of execve
}			t_info;

void	set_info(t_info *info);
t_info	*get_info(void);
void	set_debug(bool debug);
bool	get_debug(void);

t_env	*get_env_list(void);

extern t_env *g_env;
extern int	g_exit_status;

#endif
