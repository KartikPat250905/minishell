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

t_node	*init_stack_node(t_ast_node *ast_node)
{
	t_node	*node;

	node = gc_alloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = ast_node->type;
	node->ast_node = ast_node;
	node->next = NULL;
	return (node);
}

t_node	*init_node(int value)
{
	t_node	*new_node;

	new_node = gc_alloc(sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->value = value;
	return (new_node);
}
