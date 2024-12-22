/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 16:28:54 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/28 19:12:26 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_node	*init_node(int value)
{
	t_node	*new_node;

	new_node = gc_alloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	return (new_node);
}

/*
int	free_stack(t_stack *stack, int send_error)
{
	while (stack->size)
		free(pop(stack));
	free(stack);
	if (send_error)
		write(2, "Error\n", 6);
	return (0);
}
*/
