/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 16:45:05 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
//state tokentype

t_entry *actual_lookup(t_entry **table, int state, int token)
{
	int i;

	i = 0;
	while (table[i])
	{
		if (table[i]->state == state && table[i]->token_type == token)
			return (table[i]);
		i++;
	}
	return (NULL);
}

void	table_lookup(t_entry *entry, t_stack *stack, t_stack *in_stack, t_entry **table)
{
	int	top;
	int	top_in;

	top = fetch_top(stack);
	top_in = fetch_top(in_stack);
	if (is_state(top))
		entry = actual_lookup(table, top, top_in);
	if (is_non_terminal(top))
	{
		entry = actual_lookup(table, top, stack->top->next->value);
		if (!entry)
			entry = actual_lookup(table, top, -1);
	}
}

int	parsing_main(void) //char *str
{
	int		ret;
	t_stack	*stack;
	t_stack	*tokens;
	t_entry	**table;
	t_entry	*entry;

	tokens = NULL;
	entry = NULL;
	lexer(tokens);
	stack = init_stack();
	push(stack, init_node(0));
	//if (!init_node(0))
	table = create_table("srcs/parsing/parsing-table");
	ret = -1;
	while (ret == -1)
	{
		table_lookup(entry, stack, tokens, table);
		if (!entry)
			break ;
		else if (entry->state == ACCEPT)
			//return ; // TODO: handle this
			ret = 1;
		else if (entry->state == SHIFT)
			ret = action_shift(stack, tokens, entry);
		else if (entry->state == REDUCE)
			ret = action_reduce(stack, entry);
		else if (entry->state == DEFAULT)
			ret = action_goto(stack, entry);
		else
			//return ; //TODO : handle reject case
			ret = 0;
	}
	return (ret);
}
