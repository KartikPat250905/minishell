/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:33 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/30 14:43:53 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "minishell.h"

int	action_accept(void)
{
	if (get_debug())
	{
		ft_putendl_fd("-accept-", 1);
		ft_putendl_fd("parsing accepted", 1);
	}
	return (ACCEPT);
}

int	action_goto(t_stack *stack, t_entry *entry)
{
	t_node	*next_state;

	next_state = init_node(entry->go_to);
	if (!next_state)
		return (-2); //error
	push(stack, next_state);
	return (-1);
}

int	action_shift(t_stack *stack, t_entry *entry, t_token_stack *tokens)
{
	t_token_node	*popped_token;
	t_node			*token;
	t_ast_node		*ast_node;

	if (get_debug())
		ft_putendl_fd("-shift-", 1);
	popped_token = pop_token(tokens);
	if (!popped_token)
		return (-2);
	//--create_ast_node
	ast_node = init_ast_node(popped_token->type, popped_token, NULL, 0);
	if (!ast_node)
		return (-2);
	//--create_token and link ast_node
	token = init_stack_node(ast_node);
	if (!token)
		return (-2);
	push(stack, token);
	return (action_goto(stack, entry));
}

static int	create_ast_and_push(t_stack *stack, int reduce, t_ast_node **children, int non_terminal)
{
	t_ast_node	*ast_node;
	t_node		*rule;

	ast_node = init_ast_node(non_terminal, NULL, children, reduce);
	if (!ast_node)
		return (-2);
	rule = init_stack_node(ast_node);
	if (!rule)
		return (-2);
	push(stack, rule);
	return (1);
}

int	action_reduce(t_stack *stack, t_entry *entry, t_entry **table)
{
	int			non_terminal;
	int			current_state;
	t_entry		*goto_entry;
	t_ast_node	**children;

	if (get_debug())
		ft_putendl_fd("-reduce-", 1);
	non_terminal = get_non_terminal(entry->go_to);
	if (non_terminal == -1)
		return (-2);
	children = children_alloc_and_fill(stack, entry->reduce);
	if (!children)
		return (-2);
	if (!stack->top)
		return (-2);
	current_state = stack->top->value;
	if (create_ast_and_push(stack, entry->reduce, children, non_terminal) == -2)
		return (-2);
	goto_entry = non_terminal_lookup(table, current_state, non_terminal);
	if (!goto_entry)
		return (-2);
	return(action_goto(stack, goto_entry));
}
