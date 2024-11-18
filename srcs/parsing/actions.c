/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 21:37:33 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/18 15:54:05 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdio.h>

t_entry *non_terminal_lookup(t_entry **table, int state, int non_terminal)
{
	int	i;

	i = 0;
	while (table[i])
	{
		if (table[i]->state == state && 
			table[i]->token_type == non_terminal && 
			table[i]->action == GOTO)
			return (table[i]);
		i++;
	}
	return (NULL);
}

int get_non_terminal(int rule_number)
{
    switch (rule_number)
    {
        case 1: return PIPE_SEQ; // Rule 1: pipe_sequence → simple_command
        case 2: return PIPE_SEQ; // Rule 2: pipe_sequence → pipe_sequence T_PIPE simple_command
        case 3: return SIMPLE_CMD; // Rule 3: simple_command → cmd_prefix cmd_word cmd_suffix
        case 4: return SIMPLE_CMD; // Rule 4: simple_command → cmd_prefix cmd_word
        case 5: return SIMPLE_CMD; // Rule 5: simple_command → cmd_prefix
        case 6: return SIMPLE_CMD; // Rule 6: simple_command → cmd_name cmd_suffix
        case 7: return SIMPLE_CMD; // Rule 7: simple_command → cmd_name
        case 8: return CMD_NAME; // Rule 8: cmd_name → T_WORD
        case 9: return CMD_WORD; // Rule 9: cmd_word → T_WORD
        case 10: return CMD_PREFIX; // Rule 10: cmd_prefix → IO_REDIRECT
        case 11: return CMD_PREFIX; // Rule 11: cmd_prefix → cmd_prefix IO_REDIRECT
        case 12: return CMD_SUFFIX; // Rule 12: cmd_suffix → IO_REDIRECT
        case 13: return CMD_SUFFIX; // Rule 13: cmd_suffix → cmd_suffix IO_REDIRECT
        case 14: return CMD_SUFFIX; // Rule 14: cmd_suffix → WORD
        case 15: return CMD_SUFFIX; // Rule 15: cmd_suffix → cmd_suffix WORD
        case 16: return IO_REDIRECT; // Rule 16: io_redirect → io_file
        case 17: return IO_REDIRECT; // Rule 17: io_redirect → io_here
        case 18: return IO_FILE; // Rule 18: io_file → '<' filename
        case 19: return IO_FILE; // Rule 19: io_file → '>' filename
        case 20: return IO_FILE; // Rule 20: io_file → DGREAT filename
        case 21: return FILENAME; // Rule 21: filename → WORD
        case 22: return IO_HERE; // Rule 22: DLESS → here_end
        case 23: return HERE_END; // Rule 22: here_end → WORD
        default:
            ft_putendl_fd("Error: Invalid rule number", 2);
            return -1; // Indicate error
    }
}


int	action_shift(t_stack *stack, t_stack *in_stack, t_entry *entry)
{
	t_node	*popped;
	t_node	*next_state;

	ft_putendl_fd("-shift-", 1);
	//init_push(entry->go_to, stack);
	popped = pop(in_stack);
	push(stack, popped);
	next_state = init_node(entry->go_to);
	if (!next_state)
		return (-2); //error?
	push(stack, next_state);
	return (-1);
}

int	action_reduce(t_stack *stack, t_entry *entry, t_entry **table)
{
	int	rm_tokens;
	int	i;
	int	non_terminal;
	t_node	*rule;
	int	current_state;
	t_entry	*goto_entry;

	ft_putendl_fd("-reduce-", 1);
	rm_tokens = 0;
	i = entry->reduce * 2;
	//if (i < 0 || i > 3) //way too particular for this grammar
	//	return (-2);
	while(rm_tokens < i--)
		pop(stack);
	current_state = fetch_top(stack);
	non_terminal = get_non_terminal(entry->go_to);
	if (non_terminal == -1)
		return (-2);
	rule = init_node(non_terminal);
	if (!rule)
		return (-2);
	push(stack, rule);
	goto_entry = non_terminal_lookup(table, current_state, non_terminal);
	if (!goto_entry)
		return (-2); //goto entry not found
	return(action_goto(stack, goto_entry));
}

int	action_goto(t_stack *stack, t_entry *entry)
{
	t_node	*next_state;

	ft_putendl_fd("-goto-", 1);
	next_state = init_node(entry->go_to);
	if (!next_state)
		return (-2); //error
	push(stack, next_state);
	return (-1);
}
