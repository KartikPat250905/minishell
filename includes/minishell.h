#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>

# include "libft.h"
# include "gc_alloc.h"
# include "lexer.h"
# include "signals.h"
//# include "parsing.h"
# include "builtins.h"
# include "env.h"

# include <readline/readline.h>
# include <readline/history.h>

extern t_env *g_env;

#endif
