# include "minishell.h"

void	spush(t_sstack *stack, t_snode *node)
{
	if (!stack->top)
	{
		stack->top = node;
		stack->size++;
		return ;
	}
	node->next = stack->top;
	stack->top = node;
	stack->size++;
}

t_snode	*spop(t_sstack *stack)
{
	t_snode	*popped;

	if (!stack->top || !stack->size)
		return (NULL);
	popped = stack->top;
	stack->top = popped->next;
	stack->size -= 1;
	popped->next = NULL;
	return (popped);
}

t_snode	*sinit_node(char *value)
{
	t_snode	*new_node;

	new_node = gc_alloc(sizeof(t_snode));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_sstack	*sinit_stack(void)
{
	t_stack	*new_stack;

	new_stack = gc_alloc(sizeof(t_stack));
	if (!new_stack)
		return (NULL);
	new_stack->top = NULL;
	new_stack->size = 0;
	return (new_stack);
}