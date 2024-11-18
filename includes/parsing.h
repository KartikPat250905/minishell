/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:39:14 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/18 14:49:27 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdbool.h>
# include <unistd.h> //malloc(), free()
# include <fcntl.h> //open()
# include "libft.h"
# include "stack.h"
# include "gc_alloc.h"

typedef enum e_action
{
	SHIFT = 0,
	REDUCE = 1,
	ACCEPT = 2,
	GOTO = -1,
}				t_action;

typedef enum e_terminals
{
	END = 0,
	RED_FO = 60,
	RED_TO = 62,
	PIPE = 124,
	ERROR = 256,
	WORD = 258,
	DLESS = 259,
	DGREAT = 260,
}				t_token; //rename to terminal

typedef enum e_non_terminals
{
	ACCEP = 9, //defined twice, removing letter T, removable?
	PIPE_SEQ = 10,
	SIMPLE_CMD = 11,
	CMD_NAME = 12,
	CMD_WORD = 13,
	CMD_PREFIX = 14,
	CMD_SUFFIX = 15,
	IO_REDIRECT = 16,
	IO_FILE = 17,
	IO_HERE = 19,
	FILENAME = 21, //upd from 18 to 21
	HERE_END = 23, //upd from 20 to 23
	DEFAULT = -1,
}				t_rules; //rename to non_terminal

typedef struct s_entry
{
	int	state;
	int	token_type;
	int	action;
	int	go_to;
	int	reduce;
}		t_entry;

//actions.c
int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry);
int	action_reduce(t_stack *stack, t_entry *entry, t_entry **table);
int	action_goto(t_stack *stack, t_entry *entry);

//enum_check.c
bool	is_type_token(int value);
bool	is_non_terminal(int value);
bool	is_state(int value);

//fetch_safe.c
int		fetch_top(t_stack *stack);

//file.c
int	get_table_size(char *filename);
t_entry	*create_entry(char *line);
t_entry	**create_table(char *filename);

//lexer/lexer.c
void	lexer(t_stack *tokens);

//parsing.c
t_entry *actual_lookup(t_entry **table, int state, int token);
t_entry	*table_lookup(t_stack *stack, t_stack *in_stack, t_entry **table);
int		parsing_main(void);//(char *str);

#endif
