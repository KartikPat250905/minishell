/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:07:43 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 15:07:45 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

//from gpt
void print_ast(t_ast_node *node, int indent)
{
		if (!node)
			return;
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
			print_ast(node->children[i], indent + 1);
		}
}

void	print_stacks(t_stack *stack, t_token_stack *tokens)
{
	if (get_debug())
	{
		ft_putendl_fd("----------------", 1);
		if (stack->top)
			print_stack(stack, "stack");
		if (tokens->top)
			print_tokens(tokens, "tokens");
	}
}

void	print_stack(t_stack *stack, char *name)
{
	t_node *node;

	node = stack->top;
	ft_putstr_fd("---", 1);
	ft_putendl_fd(name, 1);
	while (node)
	{
		ft_putnbr_fd(node->value, 1);
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
}

void	print_tokens(t_token_stack *tokens, char *name)
{
	t_token_node *node;

	node = tokens->top;
	ft_putstr_fd("---", 1);
	ft_putendl_fd(name, 1);
	while (node)
	{
		ft_putnbr_fd(node->type, 1);
		ft_putchar_fd('(', 1);
		ft_putstr_fd(node->value, 1);
		ft_putchar_fd(')', 1);
		ft_putchar_fd('\n', 1);
		node = node->next;
	}
}
