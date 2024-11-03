# include "parsing.h"
# include "stack/stack.h"
//state tokentype

void	table_lookup(t_entry *entry, t_stack *stack)
{

}

int	parsing_main(char *str)
{
	int		ret;
	t_entry	entry;
	t_stack	*stack;
	t_node *node;

	stack = init_stack();
	node = init_node(0);
	push(stack, node);

	while (ret != ACCEPT && ret != -1)
	{
		table_lookup(&entry, stack);
	}
}
