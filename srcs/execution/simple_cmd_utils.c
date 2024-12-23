/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 21:34:54 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 21:34:56 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void	initialize_exec_info(t_exec_info *info)
{
	info->heredoc_fd = -1;
	info->redir_list = NULL;
}

void	wait_for_child(pid_t pid)
{
	int	status;
	int	signal_num;

	ignore_signals();
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		signal_num = WTERMSIG(status);
		g_exit_status = 128 + signal_num;
	}
}

void	execute_builtin_cmd(char **argv, t_exec_info *info)
{
	int	original_in;
	int	original_out;

	original_in = dup(STDIN_FILENO);
	original_out = dup(STDOUT_FILENO);
	if (!original_in || !original_out)
		return ;
	if (info->heredoc_fd != -1)
	{
		dup2(info->heredoc_fd, STDIN_FILENO);
		close(info->heredoc_fd);
	}
	if (apply_normal_redirections(info->redir_list) != EXIT_FAILURE)
		g_exit_status = execute_builtin(argv);
	dup2(original_in, STDIN_FILENO);
	dup2(original_out, STDOUT_FILENO);
	close(original_in);
	close(original_out);
}

void	execute_external_cmd(char **argv, t_exec_info *info)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (pid == 0)
	{
		activate_signal_handler();
		if (info->heredoc_fd != -1)
		{
			dup2(info->heredoc_fd, STDIN_FILENO);
			close(info->heredoc_fd);
		}
		if (apply_normal_redirections(info->redir_list) == EXIT_FAILURE)
			exit(g_exit_status);
		resolve_and_exec_cmd(argv);
	}
	else
		wait_for_child(pid);
}
