/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lookups.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 15:09:16 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 15:09:18 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"

t_entry	*non_terminal_lookup(t_entry **table, int state, int non_terminal)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (table[i]->state == state
			&& table[i]->token_type == non_terminal
			&& table[i]->action == GOTO)
			return (table[i]);
		i++;
	}
	return (NULL);
}

t_entry	*actual_lookup(t_entry **table, int state, int token)
{
	int	i;

	i = 0;
	if (!table)
		return (NULL);
	while (i < 100 && table[i])
	{
		if (table[i] && table[i]->state == state && table[i]->token_type == token)
			return (table[i]);
		i++;
	}
	return (NULL);
}

t_entry	*table_lookup(t_stack *stack, t_token_stack *tokens, t_entry **table)
{
	int		state;
	int		token;
	t_entry	*entry;

	state = -2;
	if (!stack || !tokens)
		return (NULL);
	if (stack->top)
		state = stack->top->value;
	token = -2;
	if (tokens->top)
		token = tokens->top->type;
	entry = NULL;
	entry = actual_lookup(table, state, token);
	if (!entry)
		entry = actual_lookup(table, state, DEFAULT);
	return (entry);
}
