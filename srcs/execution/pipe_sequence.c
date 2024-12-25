/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 09:39:13 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/23 16:48:49 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void	create_pipes(int *pipefds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("pipe");
			g_exit_status = EXIT_FAILURE;
			gc_free_all();
			free_env_list();
			exit(g_exit_status);
		}
		i++;
	}
}

void	execute_pipeline(t_ast_node **commands, int cmd_count)
{
	t_pipe_data	pd;
	int			i;

	pd.pipe_count = cmd_count - 1;
	pd.cmd_count = cmd_count;
	pd.pipefds = gc_alloc(pd.pipe_count * 2 * sizeof(int));
	pd.pids = gc_alloc(pd.cmd_count * sizeof(pid_t));
	create_pipes(pd.pipefds, pd.pipe_count);
	ignore_signals();
	i = 0;
	while (i < pd.cmd_count)
	{
		if (!execute_single_command(commands[i], i, &pd))
			break ;
		i++;
	}
	close_pipes(pd.pipefds, pd.pipe_count);
	wait_for_children(pd.pids, pd.cmd_count);
}

void	close_pipes(int *pipefds, int pipe_count)
{
	int	i;

	i = 0;
	while (i < pipe_count * 2)
	{
		close(pipefds[i]);
		i++;
	}
}

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int	status;
	int	i;

	i = 0;
	status = 0;
	while (i < cmd_count)
	{
		wait_for_child_pipe(pids[i], &status);
		i++;
	}
}

void	wait_for_child_pipe(pid_t pid, int *status)
{
	int	signal_num;
	int	result;

	result = waitpid(pid, status, 0);
	if (result < 0)
		return ;
	if (WIFEXITED(*status))
	{
		g_exit_status = WEXITSTATUS(*status);
		if (g_exit_status == 1)
			g_exit_status = 127;
	}
	else if (WIFSIGNALED(*status))
	{
		signal_num = WTERMSIG(*status);
		if (signal_num == SIGINT)
			g_exit_status = 130;
		get_info()->flag = 0;
	}
}
