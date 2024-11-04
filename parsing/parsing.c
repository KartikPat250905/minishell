#include "parsing.h"
//state tokentype

void	table_lookup(t_entry *entry, t_stack *stack, t_stack *in_stack)
{
	int	top;
	int	top_in;

	top = fetch_top(stack);
	top_in = fetch_top(in_stack);
	if (is_state(top))
		actual_lookup(entry, top, top_in);
	if (is_non_terminal(top))
		actual_lookup(entry, top, top->next->value);
}

/*
 * Hardcored lexer just to be able to test the LR parsing algo, 
 * we obviously need a proper lexer that takes the original raw string
 * and returns a stack of input tokens, remember, 
 * we are reading from left to right, so we fill the stack from right to left
 *
 * test case: 
 * ls > outfile EOF
 * WORD RET_TO WORD EOF
 *
 * btw, should prototype be?
 * int lexer(char *str, t_stack *input_tokens);
 * 
 * or
 *
 * t_stack *lexer(char *str);
 */
void	lexer(t_stack *tokens)
{
	tokens = init_stack();
	//if (!input_tokens)
	push(tokens, init_node(END)); //EOF
	push(tokens, init_node(WORD)); //outfile
	//if (!init_node(WORD))
	push(tokens, init_node(RET_TO)); //>
	push(tokens, init_node(WORD)); //ls
}

int	parsing_main(char *str)
{
	int		ret;
	t_stack	*stack;
	t_stack	*tokens;
	t_entry	entry;

	lexer(tokens);
	stack = init_stack();
	push(stack, init_node(0));
	//if (!init_node(0))
	ret = -1;
	while (ret == -1)
	{
		table_lookup(&entry, stack, tokens);
		if (entry.state == ACCEPT)
			//return ; // TODO: handle this
			ret = 1;
		else if (entry.state == SHIFT)
			ret = action_shift(stack, tokens, entry);
		else if (entry.state == REDUCE)
			ret = action_reduce(stack, tokens, entry);
		else if (entry.state == DEFAULT)
			ret = action_goto(stack, tokens, entry);
		else
			//return ; //TODO : handle reject case
			ret = 0;
	}
}
