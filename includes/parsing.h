/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:39:14 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 13:43:34 by aapadill         ###   ########.fr       */
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
	SHIFT,
	REDUCE,
	ACCEPT,
	DEFAULT = -1,
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
}				t_token;

typedef enum e_non_terminals
{
	//ACCEPT = 9, //defined twice? //necessary?
	PIPE_SEQ = 10,
	SIMPLE_CMD = 11,
	CMD_NAME = 12,
	CMD_WORD = 13,
	CMD_PRE = 14,
	CMD_SUFFIX = 15,
	IO_REDIRECT = 16,
	IO_FILE = 17,
	FILENAME = 18,
	IO_HERE = 19,
	HERE_END = 20,
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
int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry);
int	action_reduce(t_stack *stack, t_entry *entry);
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
void	table_lookup(t_entry *entry, t_stack *stack, t_stack *in_stack, t_entry **table);
int		parsing_main(void);//(char *str);

#endif
