# include "parsing.h"

int	fetch_top(t_stack *stack)
{
	if (stack -> top)
		return (stack->top->value);
	return (-1);
}