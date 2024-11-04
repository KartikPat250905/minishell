# include "parsing.h"

int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	init_push(entry->go_to, stack);
	return (-1);
}

int	action_reduce(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	int	rm_tokens;

	rm_tokens = 0;
	while(rm_tokens < (entry->reduce * 2))
		pop(stack);
	return (-1);
}