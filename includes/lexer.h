#ifndef LEXER_H
# define LEXER_H

# include "minishell.h"

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

typedef enum e_quotes
{
	NORMAL=0,
	DOUBLE_QUOTES=1
}			t_quote_state;

typedef struct s_lexer_iterators
{
	int		start;
	int		cur;
	int		len;
	char	quote_char;
	char	*input;
}				t_iterators;

typedef struct s_token_node
{
	int					type;
	char				*value;
	t_quote_state		state;
	struct s_token_node	*next;
}	t_token_node;

typedef struct s_token_stack
{
	t_token_node	*top;
	size_t	size;
}	t_token_stack;

void	handle_space(t_iterators *it);
bool	tokenize_pipe(t_iterators *it, t_token_stack *stack);
bool	tokenize_output(t_iterators *it, t_token_stack *stack);
bool	tokenize_input(t_iterators *it, t_token_stack *stack);
bool	tokenize_quotes(t_iterators *it, t_token_stack *stack);
bool	tokenize_words(t_iterators *it, t_token_stack *stack);

t_token_node	*create_token(t_token type, char *value);
t_token_stack	*init_token_stack(void);
void	print_token_stack(t_token_stack *stack, char *name);
t_token_node	*pop_token(t_token_stack *stack);
void	push_token(t_token_stack *stack, t_token_node *node);

bool	is_token(char ch, char next);
t_token_stack	*lexer(char *input);

#endif
