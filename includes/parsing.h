/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:39:14 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/26 18:57:20 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h> //open()
# include "minishell.h"

/* -------------------------------------------------------------------------- */
/*                                   STACK                                    */
/* -------------------------------------------------------------------------- */

typedef struct s_node
{
	int				value;
	struct s_node	*next;
}	t_node;

typedef struct s_stack
{
	t_node	*top;
	size_t	size;
}	t_stack;

t_node	*init_node(int value);
t_stack	*init_stack(void);
void	push(t_stack *stack, t_node *new_node);
t_node	*pop(t_stack *stack);
void	print_stack(t_stack *stack, char *name);
//int	free_stack(t_stack *stack, int send_error);

/* -------------------------------------------------------------------------- */
/*                                  PARSING                                   */
/* -------------------------------------------------------------------------- */

typedef enum e_action
{
	SHIFT = 0,
	REDUCE = 1,
	ACCEPT = 2,
	GOTO = -1,
}				t_action;

typedef enum e_non_terminals
{
	ACCEP = 9,
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
}				t_rules;

typedef struct s_entry
{
	int	state;
	int	token_type;
	int	action;
	int	go_to;
	int	reduce;
}		t_entry;

//actions.c
int	action_shift(t_stack *stack, t_token_stack *in_stack, t_entry *entry);
int	action_reduce(t_stack *stack, t_entry *entry, t_entry **table);
int	action_goto(t_stack *stack, t_entry *entry);

//enum_check.c
bool	is_type_token(int value);
bool	is_non_terminal(int value);
bool	is_state(int value);

//fetch_safe.c
//int		fetch_top(t_stack *stack);

//file.c
int	get_table_size(char *filename);
t_entry	*create_entry(char *line);
t_entry	**create_table(char *filename);

//parsing.c
t_entry *actual_lookup(t_entry **table, int state, int token);
t_entry	*table_lookup(t_stack *stack, t_token_stack *in_stack, t_entry **table);
int		parsing_main(void);//(char *str);

#endif
