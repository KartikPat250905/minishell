/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_heredoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 00:04:41 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/24 00:04:42 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void	handle_heredoc_child(char *end_word, int write_fd)
{
	char *line;

	//close(STDIN_FILENO); //not sure
	signal(SIGINT, free_exit);
	signal(SIGQUIT, SIG_DFL);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, end_word) == 0)
		{
			free(line);
			break;
		}
		ft_putendl_fd(line, write_fd);
		free(line);
	}
	close(write_fd);
	gc_free_all();
	exit(EXIT_SUCCESS);
}

void	handle_heredoc(char *end_word, t_exec_info *info)
{
	int pipefd[2];
	pid_t hd_pid;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return ;
	}
	hd_pid = fork();
	if (hd_pid < 0)
	{
		perror("fork");
		close(pipefd[0]);
		close(pipefd[1]);
		return ;
	}
	else if (hd_pid == 0)
		handle_heredoc_child(end_word, pipefd[1]);
	else
	{
		close(pipefd[1]);
		wait_for_child(hd_pid);
		info->heredoc_fd = pipefd[0];
	}
}
