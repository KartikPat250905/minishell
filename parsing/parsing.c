# include "parsing.h"
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
		actual_lookup(entry, top, stack -> top -> next -> value);
}

int	parsing_main(char *str, t_stack *in_stack)
{
	int		ret;
	t_entry	entry;
	t_stack	*stack;

	stack = init_stack();
	init_push(0, stack);
	while (ret != ACCEPT && ret != -1)
	{
		table_lookup(&entry, stack, in_stack);
		if (entry.state == ACCEPT)
			return ; // TODO: handle this
		else if (entry.state == SHIFT)
			ret = action_shift(stack, in_stack, entry);
		else if (entry.state == REDUCE)
			ret = action_reduce(stack, in_stack, entry);
		else
			return ; //TODO : handle reject case
	}
}
