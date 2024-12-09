/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:48:02 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/06 10:48:06 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void	execute_ast(t_ast_node *node)
{
	if (!node)
		return ;
	if (node->type == SIMPLE_CMD)
	{
		execute_simple_cmd(node);
	}
	else if (node->type == PIPE_SEQ)
	{
		//execute_pipe_seq(node);
		execute_ast(node->children[0]);
	}
}