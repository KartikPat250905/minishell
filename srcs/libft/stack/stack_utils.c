/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:28:54 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 12:24:00 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stack.h"

t_node	*init_node(int value)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	new_node->next = NULL;
	return (new_node);
}

t_stack	*init_stack(void)
{
	t_stack	*new_stack;

	new_stack = malloc(sizeof(t_stack));
	if (!new_stack)
		return (NULL);
	new_stack->top = NULL;
	new_stack->size = 0;
	return (new_stack);
}

/*
void	init_push(int value, t_stack *stack)
{
	t_node	*node;

	node = init_node(value);
	push(stack, node);
}
*/

int	free_stack(t_stack *stack, int send_error)
{
	while (stack->size)
		free(pop(stack));
	free(stack);
	if (send_error)
		write(2, "Error\n", 6);
	return (0);
}
