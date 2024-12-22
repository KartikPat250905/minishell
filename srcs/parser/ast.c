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

t_ast_node	**children_alloc_and_fill(t_stack *stack, int reduce)
{
	t_ast_node	**children;
	t_node		*state;
	t_node		*symbol;
	int			i;

	if (reduce < 1)
		return (NULL);
	children = gc_alloc(sizeof(t_ast_node *) * reduce);
	if (!children)
		return (NULL);
	i = reduce;
	while (0 < i--)
	{
		state = pop(stack);
		if (!state)
			return (NULL);
		symbol = pop(stack);
		if (!symbol)
			return (NULL);
		if (symbol->ast_node)
			children[i] = symbol->ast_node;
		else
			children[i] = NULL;
	}
	return (children);
}

t_ast_node	*init_ast_node(int type, t_token_node *token, t_ast_node **children, int child_count)
{
	t_ast_node	*ast_node;

	ast_node = gc_alloc(sizeof(t_ast_node));
	if (!ast_node)
		return (NULL);
	ast_node->type = type;
	ast_node->token = token;
	ast_node->children = children;
	ast_node->child_count = child_count;
	return (ast_node);
}

t_ast_node *get_ast_root(t_stack *stack)
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
