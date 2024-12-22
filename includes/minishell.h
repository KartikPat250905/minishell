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
# include <termios.h>
//# include "execution.h"

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token_stack	t_token_stack;
typedef struct s_ast_node		t_ast_node;

typedef struct s_info
{
	bool						debug;
	bool						flag;
	t_token_stack				*tokens;
	t_env						*env; //head of a linked list
	int							exit_status;
	t_ast_node					*ast;
	char						**envp; //move here //array //because of execve
}						t_info;

t_info							*get_info(void);
bool							get_debug(void);

extern int						g_exit_status;

#endif
