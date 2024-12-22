/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:46:00 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/02 18:46:03 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

t_ast_node	*get_ast_root(t_stack *stack)
{
	t_node	*current;

	current = stack->top;
	while (current)
	{
		if (current->ast_node && current->value != END)
		{
			return (current->ast_node);
		}
		current = current->next;
	}
	return (NULL);
}
