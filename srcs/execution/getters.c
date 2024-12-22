/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:09:27 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 19:09:30 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

t_ast_node	**get_simple_cmds(t_ast_node *node, int *count)
{
	t_ast_node	**simple_cmds;
	t_ast_node	**left_cmds;
	int			i;
	int	left_count;

	if (node->child_count == 1) //kinda hardcoded, is this creating the segfault?
	{
		simple_cmds = gc_alloc(sizeof(t_ast_node *));
		//if (!simple_cmds)
		simple_cmds[0] = node->children[0];
		*count = 1;
		return (simple_cmds);
	}
	left_cmds = get_simple_cmds(node->children[0], &left_count);
	simple_cmds = gc_alloc(sizeof(t_ast_node *) * (left_count + 1));
	//if (!simple_cmds)
	i = 0;
	while (i < left_count)
	{
		simple_cmds[i] = left_cmds[i];
		i++;
	}
	simple_cmds[left_count] = node->children[2];
	*count = left_count + 1;
	return (simple_cmds);
}

int get_redirect_type(t_ast_node *io_redirect_node)
{
	t_ast_node *child;
	t_ast_node *op_node;

	child = io_redirect_node->children[0];
	if (child->type == IO_FILE)
	{
		op_node = child->children[0];
		if (op_node->token->type == RED_FO)
			return (RED_FO);
		else if (op_node->token->type == RED_TO)
			return (RED_TO);
		else if (op_node->token->type == DGREAT)
			return (DGREAT);
	}
	else if (child->type == IO_HERE)
	{
		op_node = child->children[0];
		if (op_node->token->type == DLESS)
			return (DLESS);
	}
	return (-1);
}

char *get_filename(t_ast_node *io_redirect_node)
{
	t_ast_node *child;
	t_ast_node *filename;
	t_ast_node *here_end;
	t_ast_node *word;

	child = io_redirect_node->children[0];
	if (child->type == IO_FILE)
	{
		filename = child->children[1];
		word = filename->children[0];
		return (word->token->value);
	}
	else if (child->type == IO_HERE)
	{
		here_end = child->children[1];
		word = here_end->children[0];
		return (word->token->value);
	}
	return (NULL);
}

char *get_here_end_word(t_ast_node *io_redirect)
{
	t_ast_node *io_here;
	t_ast_node *here_end;
	t_ast_node *word;

	io_here = io_redirect->children[0];
	here_end = io_here->children[1];
	word = here_end->children[0];
	return (word->token->value);
}
