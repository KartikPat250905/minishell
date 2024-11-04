/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:39:14 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/04 21:39:16 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>
# include <stdbool.h>
# include "stack/stack.h"

typedef enum e_action
{
	SHIFT,
	REDUCE,
	ACCEPT,
	DEFAULT = -1;
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

bool	is_type_token(int value);
int		fetch_top(t_stack *stack);
bool	is_non_terminal(int value);

#endif
