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

void	create_pipes(int *pipefds, int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("pipe");
			g_exit_status = EXIT_FAILURE;
			exit(g_exit_status);
		}
		i++;
	}
}

void	close_pipes(int *pipefds, int pipe_count)
{
	int i;

	i = 0;
	while (i < pipe_count * 2)
	{
		close(pipefds[i]);
		i++;
	}
}

void	wait_for_child_pipe(pid_t pid, int *status)
{
	int	signal_num;

	waitpid(pid, status, 0);
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
	}
}

void	wait_for_children(pid_t *pids, int cmd_count)
{
	int status;
	int i;

	i = 0;
	while (i < cmd_count)
	{
		wait_for_child_pipe(pids[i], &status);
		i++;
	}
}

bool	prepare_execution(t_ast_node *command, t_exec_info *info)
{
	activate_signal_handler();
	gather_redirects(command, info);
	if (g_exit_status == 130 || get_info()->flag == 0)
	{
		activate_signal_parent();
		return (false);
	}
	return (true);
}

void	apply_heredoc_redirect(t_exec_info *info)
{
	if (info->heredoc_fd != -1)
	{
		if (dup2(info->heredoc_fd, STDIN_FILENO) < 0)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(info->heredoc_fd);
	}
}

void	setup_child_pipes(t_pipe_data *pd, int index)
{
	if (index > 0)
	{
		if (dup2(pd->pipefds[(index - 1) * 2], STDIN_FILENO) < 0)
		{
			perror("dup2 input");
			exit(EXIT_FAILURE);
		}
	}
	if (index < pd->cmd_count - 1)
	{
		if (dup2(pd->pipefds[index * 2 + 1], STDOUT_FILENO) < 0)
		{
			perror("dup2 output");
			exit(EXIT_FAILURE);
		}
	}
	close_pipes(pd->pipefds, pd->pipe_count);
}

void	handle_child_process(t_pipe_data *pd, int index, t_exec_info *info, char **argv)
{
	setup_child_pipes(pd, index);
	apply_heredoc_redirect(info);
	apply_normal_redirections(info->redir_list);
	execute_simple_piped_cmd(argv);
	exit(EXIT_FAILURE);
}

bool	execute_single_command(t_ast_node *command, int index, t_pipe_data *pd)
{
	t_exec_info	info;
	char		**argv;

	initialize_exec_info(&info);
	if (!prepare_execution(command, &info))
		return (false);
	argv = build_argv(command);
	if (!argv || g_exit_status == 130)
	{
		activate_signal_parent();
		return (false);
	}
	pd->pids[index] = fork();
	if (pd->pids[index] < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pd->pids[index] == 0)
		handle_child_process(pd, index, &info, argv);
	return (true);
}

void execute_all_commands_in_pipeline(t_ast_node **commands, t_pipe_data *pd)
{
	int i;

	i = 0;
	ignore_signals();
	while (i < pd->cmd_count)
	{
		if (!execute_single_command(commands[i], i, pd))
			break ;
		i++;
	}
}

void	execute_pipeline(t_ast_node **commands, int cmd_count)
{
	t_pipe_data pd;

	pd.pipe_count = cmd_count - 1;
	pd.cmd_count = cmd_count;
	pd.pipefds = gc_alloc(pd.pipe_count * 2 * sizeof(int));
	pd.pids = gc_alloc(pd.cmd_count * sizeof(pid_t));
	
	create_pipes(pd.pipefds, pd.pipe_count);
	execute_all_commands_in_pipeline(commands, &pd);
	close_pipes(pd.pipefds, pd.pipe_count);
	wait_for_children(pd.pids, pd.cmd_count);
}
