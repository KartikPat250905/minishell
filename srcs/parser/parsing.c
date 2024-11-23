/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/23 15:30:44 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_entry *actual_lookup(t_entry **table, int state, int token)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (table[i]->state == state && table[i]->token_type == token)
			return (table[i]);
		i++;
	}
	return (NULL);
}

t_entry	*table_lookup(t_stack *stack, t_stack *in_stack, t_entry **table)
{
	int	top;
	int	top_in;
	t_entry *entry;

	top = fetch_top(stack);
	top_in = fetch_top(in_stack);
	entry = NULL;
	//if (is_state(top))
	//{
		entry = actual_lookup(table, top, top_in);
		if (!entry)
	//	{
			entry = actual_lookup(table, top, DEFAULT);
	//	}
	//}
	//else if (is_non_terminal(top))
	//	entry = actual_lookup(table, top, stack->top->next->value);
	return (entry);
}

int	parsing_main(void) //char *str
{
	int		ret;
	//t_stack	*stack;
	t_token_stack *tokens;
	//t_entry	**table;
	t_entry	*entry;

	tokens = NULL;
	entry = NULL;
	ret = 0;
	tokens = init_token_stack();
	tokens = lexer("echo \"kartik is\"|echo 'shit'");
	// stack = init_stack();
	// push(stack, init_node(0));
	// //if (!init_node(0))
	// table = create_table("srcs/parser/parsing-table");
	// ret = -1;
	// while (ret == -1)
	// {
	// 	ft_putendl_fd("----------------", 1);
	// 	print_stack(stack, "stack");
	// 	ft_putendl_fd("", 1);
	// 	print_stack(tokens, "tokens");
	// 	entry = table_lookup(stack, tokens, table);
	// 	if (!entry)
	// 	{
	// 		ret = 2;
	// 		break ;
	// 	}
	// 	else if (entry->action == ACCEPT)
	// 		ret = 1;
	// 	else if (entry->action == SHIFT)
	// 		ret = action_shift(stack, tokens, entry);
	// 	else if (entry->action == REDUCE)
	// 		ret = action_reduce(stack, entry, table);
	// 	else
	// 		ret = 0;
	// }
	//ft_putendl_fd("----------------leftovers", 1);
	//print_stack(stack, "stack");
	//ft_putendl_fd("", 1);
	//print_stack(tokens, "tokens");
	return (ret);
}
