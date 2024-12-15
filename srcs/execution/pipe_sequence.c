/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:39:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/10 09:39:14 by aapadill         ###   ########.fr       */
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

	//just one simple command
	//pipe_sequence -> simple_command
	if (node->child_count == 1)
	{
		simple_cmds = gc_alloc(sizeof(t_ast_node *));
		simple_cmds[0] = node->children[0];
		*count = 1;
		return (simple_cmds);
	}
	//more than one simple command
	//pipe_sequence -> simple_command PIPE pipe_sequence
	else
	{
		left_cmds = get_simple_cmds(node->children[0], &left_count);
		simple_cmds = gc_alloc(sizeof(t_ast_node *) * (left_count + 1));
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
}

void	execute_pipeline(t_ast_node **command, int cmd_count)
{
	int pipe_count;
	int	pipefds[2 * (cmd_count - 1)];
	int	i;
	int	j;
	pid_t	pid;

	i = 0;
	pipe_count = cmd_count - 1;
	//create pipes
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("pipe");
			//return ;
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			//return ;
			exit(1);
		}
		else if (pid == 0) //child
		{
			//if not first command
			if (i > 0)
			{
				dup2(pipefds[(i-1) * 2], STDIN_FILENO);
				//protect dup2
			}
			//if not last command
			if (i < cmd_count - 1)
			{
				dup2(pipefds[i * 2 + 1], STDOUT_FILENO);
				//protect dup2
			}
			//close all pipes
			j = 0;
			while (j < pipe_count * 2)
			{
				close(pipefds[j]);
				j++;
			}
			execute_simple_cmd(command[i]);
			//ft_putstr_fd("what is this case?", STDERR_FILENO);
			exit(1);
		}
		i++;
	}

	//close all pipes
	j = 0;
	while (j < pipe_count * 2)
	{
		close(pipefds[j]);
		j++;
	}
	//wait for all children
	i = 0;
	while (i < cmd_count)
	{
		wait(NULL);
		i++;
	}
}

void	execute_pipe_seq(t_ast_node *node)
{
	int	count;
	t_ast_node	**simple_cmds;

	simple_cmds = get_simple_cmds(node, &count);
	if (count == 1)
	{
		execute_simple_cmd(simple_cmds[0]);
	}
	else
	{
		//execute multiple simple commands
		execute_pipeline(simple_cmds, count);
	}
	//free?
}