/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:23:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/27 17:23:03 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
