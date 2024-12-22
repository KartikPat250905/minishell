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

void	execute_pipeline(t_ast_node **commands, int cmd_count)
{
	int pipe_count;
	int	pipefds[2 * (cmd_count - 1)];
	//pid_t	pid;
	pid_t	*pid;
	int		status;
	int	i;
	int	j;

	i = 0;
	pipe_count = cmd_count - 1;
	pid = gc_alloc(cmd_count * sizeof(pid_t));
	//create pipes
	while (i < pipe_count)
	{
		if (pipe(pipefds + i * 2) < 0)
		{
			perror("pipe");
			exit(EXIT_FAILURE); //is this the correct exit code
		}
		i++;
	}
	i = 0;
	ignore_signals();
	while (i < cmd_count)
	{
		//leaving in here for now but separate into a function
		t_exec_info info;
		char **argv;
		info.heredoc_fd = -1;
		info.redir_list = NULL;

		//before forking
		activate_signal_handler();
		gather_redirects(commands[i], &info);
		if (g_exit_status == 130 || get_info()->flag == 0)
		{
			activate_signal_parent();
			break ;
		}
		//build argv
		argv = build_argv(commands[i]);
		if (g_exit_status == 130)
		{
			activate_signal_parent();
			break ;
		}
		pid[i] = fork();
		//pid = fork();
		if (pid[i] < 0)
		//if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid[i] == 0) //child
		{
			//if not first command
			if (i > 0)
			{
				if (dup2(pipefds[(i-1) * 2], STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			//if not last command
			if (i < cmd_count - 1)
			{
				if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			//close all pipes
			j = 0;
			while (j < pipe_count * 2)
			{
				close(pipefds[j]);
				j++;
			}
			//apply heredoc
			if (info.heredoc_fd != -1)
			{
				if (dup2(info.heredoc_fd, STDIN_FILENO) < 0)
				{
					perror("dup2 heredoc");
					exit(EXIT_FAILURE);
				}
				close(info.heredoc_fd);
			}
			apply_normal_redirections(info.redir_list);
			execute_simple_piped_cmd(argv);
			exit(EXIT_FAILURE);
		}
		//parent
		i++;
	}
	//parent
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
		waitpid(pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_exit_status = WEXITSTATUS(status);
			if (g_exit_status == 1)
				g_exit_status = 127;
		}
		else if (WIFSIGNALED(status))
		{
			int signal_num = WTERMSIG(status);
			if (signal_num == SIGINT)
			{
				g_exit_status = 130;
			}
		}
		i++;
	}
}
