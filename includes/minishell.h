/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:43:10 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/25 11:43:11 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define EXIT_PARSE_ERROR 2

# include <stdio.h>
# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include "libft.h"
# include "gc_alloc.h"
# include "lexer.h"
# include "signals.h"
# include "builtins.h"
# include "env.h"
# include <termios.h>

# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_token_stack	t_token_stack;
typedef struct s_ast_node		t_ast_node;
typedef struct s_entry			t_entry;

typedef struct s_info
{
	bool						debug;
	bool						break_flag;
	bool						flag;
	t_env						*env;
	int							exit_status;
	t_token_stack				*tokens;
	t_entry						**table;
	t_ast_node					*ast;
	char						**envp;
}						t_info;

t_info							*get_info(void);
bool							get_debug(void);

extern int						g_exit_status;

void							free_and_exit(void);
void							init_terminal_set(void);
void							reset_to_tty(void);

#endif
