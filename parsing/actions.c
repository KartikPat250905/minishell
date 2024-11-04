#include "parsing.h"

int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	t_node	*popped;
	t_node	*next_state;

	//init_push(entry->go_to, stack);
	popped = pop(in_stack);
	push(popped, stack);
	next_state = init_node(entry->go_to);
	//if (!next_state)
	push(next_state, stack);
	return (-1); //mmm why?
}

int	action_reduce(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	int	rm_tokens;
	int	i;
	t_node	*rule;

	rm_tokens = 0;
	i = entry->reduce * 2;
	while(rm_tokens < i--)
		pop(stack);
	rule = init_node(entry->go_to);
	//if (!rule)
	push(next_state, stack);
	return (-1);
}

int	action_goto(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	t_node	*next_state;

	next_state = init_node(entry->go_to);
	//if (!next_state)
	push(next_state, stack);
	return (-1);
}
