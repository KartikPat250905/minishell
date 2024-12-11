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

bool	is_builtin(char *cmd_name)
{
	if (!ft_strcmp(cmd_name, "echo"))
		return (true);
	else if (!ft_strcmp(cmd_name, "cd"))
		return (true);
	else if (!ft_strcmp(cmd_name, "pwd"))
		return (true);
	else if (!ft_strcmp(cmd_name, "export"))
		return (true);
	else if (!ft_strcmp(cmd_name, "unset"))
		return (true);
	else if (!ft_strcmp(cmd_name, "env"))
		return (true);
	else if (!ft_strcmp(cmd_name, "exit"))
		return (true);
	return (false);
}

int	execute_builtin(char **argv)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (ft_echo(argv));
	else if (!ft_strcmp(argv[0], "cd"))
		return (ft_cd(argv));
	else if (!ft_strcmp(argv[0], "pwd"))
		return (ft_pwd(argv));
	else if (!ft_strcmp(argv[0], "export"))
		return (ft_export(argv));
	else if (!ft_strcmp(argv[0], "env"))
		return (!ft_env(argv));
	/*
	else if (!ft_strcmp(argv[0], "unset"))
		ft_unset(argv);
	else if (!ft_strcmp(argv[0], "exit"))
		ft_exit(argv);
	*/
	return (0);
}

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
		execute_pipe_seq(node);
	}
}
