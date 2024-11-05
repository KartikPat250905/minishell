/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:33 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 17:39:17 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	t_node	*popped;
	t_node	*next_state;

	ft_putendl_fd("-shift-", 1);
	//init_push(entry->go_to, stack);
	popped = pop(in_stack);
	push(stack, popped);
	next_state = init_node(entry->go_to);
	if (!next_state)
		return (-2); //error?
	push(stack, next_state);
	return (-1);
}

int	action_reduce(t_stack *stack, t_entry *entry)
{
	int	rm_tokens;
	int	i;
	t_node	*rule;

	ft_putendl_fd("-reduce-", 1);
	rm_tokens = 0;
	i = entry->reduce * 2;
	while(rm_tokens < i--)
		pop(stack);
	rule = init_node(entry->go_to);
	if (!rule)
		return (-2); //error?
	push(stack, rule);
	return (-1);
}

int	action_goto(t_stack *stack, t_entry *entry)
{
	t_node	*next_state;

	ft_putendl_fd("-goto-", 1);
	next_state = init_node(entry->go_to);
	if (!next_state)
		return (-2); //error
	push(stack, next_state);
	return (-1);
}
