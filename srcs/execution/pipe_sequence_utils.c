/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 21:15:50 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/23 21:15:51 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

bool	execute_single_command(t_ast_node *command, int index, t_pipe_data *pd)
{
	t_exec_info	info;
	char		**argv;

	initialize_exec_info(&info);
	activate_signal_handler();
	gather_redirects(command, &info);
	argv = build_argv(command);
	if (!argv || g_exit_status == 130 || get_info()->flag == 0)
	{
		activate_signal_parent();
		return (false);
	}
	pd->pids[index] = fork();
	if (pd->pids[index] < 0)
	{
		perror("fork");
		gc_free_all();
		free_env_list();
		exit(EXIT_FAILURE);
	}
	else if (pd->pids[index] == 0)
		handle_child_process(pd, index, &info, argv);
	return (true);
}

void	setup_child_pipes(t_pipe_data *pd, int index)
{
	if (index > 0)
	{
		if (dup2(pd->pipefds[(index - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("dup2 input");
			gc_free_all();
			free_env_list();
			exit(EXIT_FAILURE);
		}
	}
	if (index < pd->cmd_count - 1)
	{
		if (dup2(pd->pipefds[index * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2 output");
			gc_free_all();
			free_env_list();
			exit(EXIT_FAILURE);
		}
	}
	close_pipes(pd->pipefds, pd->pipe_count);
}

void	handle_child_process(t_pipe_data *pd, int index,
		t_exec_info *info, char **argv)
{
	setup_child_pipes(pd, index);
	if (info->heredoc_fd != -1)
	{
		if (dup2(info->heredoc_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 heredoc");
			gc_free_all();
			free_env_list();
			exit(EXIT_FAILURE);
		}
		close(info->heredoc_fd);
	}
	apply_normal_redirections_piped(info->redir_list);
	execute_simple_piped_cmd(argv);
	free_env_list();
	gc_free_all();
	exit(EXIT_FAILURE);
}
