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

void	print_indent(int indent)
{
	int	i;

	while (i < indent)
	{
		printf("\t");
		i++;
	}
}

void	print_ast(t_ast_node *node, int indent)
{
	int	i;

	if (!node)
		return ;
	print_indent(indent);
	if (node->token)
	{
		printf("%s, value=%s\n",
			get_symbol_name(node->type), node->token->value);
	}
	else
	{
		printf("%s, children: %d\n",
			get_symbol_name(node->type), node->child_count);
	}
	i = 0;
	while (i < node->child_count)
	{
		print_ast(node->children[i], indent + 1);
		i++;
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
	t_node	*node;

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
	t_token_node	*node;

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
