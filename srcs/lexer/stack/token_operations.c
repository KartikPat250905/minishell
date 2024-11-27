#include "lexer.h"

void	push_token(t_token_stack *stack, t_token_node *node)
{
	if (!stack -> top)
	{
		stack -> top = node;
		stack->size++;
		return ;
	}
	node -> next = stack -> top;
	stack -> top = node;
	stack -> size ++;
}

t_token_node	*pop_token(t_token_stack *stack)
{
	t_token_node	*popped;

	if (!stack -> top || !stack -> size)
		return (NULL);
	popped = stack -> top;
	stack -> top = popped -> next;
	stack -> size --;
	popped -> next = NULL;
	return (popped);
}
