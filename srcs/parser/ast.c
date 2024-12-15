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

t_ast_node *get_ast_root(t_stack *stack)
{
    t_node *current = stack->top;

	while (current)
	{
		if (current->ast_node && current->value != END)
		{
    		return current->ast_node;
        }
        current = current->next;
    }
    return NULL;
}

/*
t_ast_node	*get_ast_root(t_stack *stack)
{
	t_node	*root;

	if (!stack | !stack->top | !stack->top->next)
		return (NULL);
	root = stack->top->next;
	if (root && root->ast_node)
		return (root->ast_node);
	return (NULL);
}*/

//from gpt
void traverse_ast(t_ast_node *node, int indent)
{
    if (!node)
        return;

    // Print indentation
    for (int i = 0; i < indent; i++)
        printf("\t"); // Two spaces per indent level

    if (node->token)
    {
        // It's a terminal node
        printf("%s, value=%s\n", get_symbol_name(node->type), node->token->value);
    }
    else
    {
        // It's a non-terminal node
        printf("%s, children: %d\n", get_symbol_name(node->type), node->child_count);
    }

    // Recursively traverse child nodes
    for (int i = 0; i < node->child_count; i++)
    {
        traverse_ast(node->children[i], indent + 1);
    }
}
