/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/30 15:05:48 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

static t_stack	*init_parsing_stack(void)
{
	t_stack	*stack;
	t_node	*node;

	stack = gc_alloc(sizeof(t_stack));
	if (!stack)
		return (NULL);
	node = init_node(0);
	if (!node)
	{
		gc_free(stack);
		return (NULL);
	}
	push(stack, node);
	return (stack);
}

static int	parsing_loop(t_stack *stack)
{
	int		ret;
	t_entry	*entry;

	entry = NULL;
	ret = -1;
	while (ret == -1)
	{
		if (get_debug())
			print_stacks(stack, get_info()->tokens);
		entry = table_lookup(stack, get_info()->tokens, get_info()->table);
		if (!entry)
		{
			ret = -2;
			break ;
		}
		else if (entry->action == ACCEPT)
			ret = action_accept();
		else if (entry->action == SHIFT)
			ret = action_shift(stack, entry, get_info()->tokens);
		else if (entry->action == REDUCE)
			ret = action_reduce(stack, entry, get_info()->table);
		else
			ret = 0;
	}
	return (ret);
}

int	parser(void)
{
	int		ret;
	t_stack	*stack;

	get_info()->table = create_table();
	stack = init_parsing_stack();
	if (!get_info()->table || !stack)
	{
		g_exit_status = EXIT_FAILURE;
		get_info()->break_flag = true;
		return (-2);
	}
	ret = parsing_loop(stack);
	if (ret == ACCEPT)
	{
		get_info()->ast = get_ast_root(stack);
		if (get_debug())
		{
			ft_putendl_fd("-------ast--------", 1);
			print_ast(get_info()->ast, 0);
		}
	}
	else
		get_info()->ast = NULL;
	return (ret);
}
