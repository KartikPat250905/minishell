#ifndef PARSING_H
# define PARSING_H

# include <unistd.h>

typedef enum e_action
{
	SHIFT,
	REDUCE,
	ACCEPT,
}				t_action;

typedef enum e_token_type
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
	ACCEPT = 9,
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

#endif
