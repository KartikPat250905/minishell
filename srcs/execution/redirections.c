/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:18:24 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 19:18:26 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void gather_redirects(t_ast_node *node, t_exec_info *info)
{
	int type;
	int pipefd[2];
	char *line;
	t_redir_info *redir_info;
	int i;

	if (!node)
		return;

	if (node->type == IO_REDIRECT)
	{
		type = get_redirect_type(node);
		if (type == DLESS) // <<
		{
			char *end_word = get_here_end_word(node);
			if (pipe(pipefd) == -1)
			{
				perror("pipe");
				return;
			}
			pid_t hd_pid = fork();
			if (hd_pid < 0)
			{
				perror("fork");
				close(pipefd[0]);
				close(pipefd[1]);
				return;
			}
			else if (hd_pid == 0)
			{
				// CHILD: read lines from heredoc and write them to pipe
				// We only keep the write end open
				close(pipefd[0]);

				// Typically you want a child to have default signals or
				// a minimal custom signal handler that leads to exit(130) on Ctrl+C
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);

				while (1)
				{
					line = readline("heredoc> ");
					if (!line || ft_strcmp(line, end_word) == 0)
					{
						free(line);
						break;
					}
					ft_putendl_fd(line, pipefd[1]);
					free(line);
				}
				close(pipefd[1]);
				// If user pressed Ctrl+C, the child is killed—this is fine
				exit(0);
			}
			else
			{
				// PARENT: We only want to read from the pipe
				close(pipefd[1]);

				// Wait for the child to finish or be interrupted
				int status;
				waitpid(hd_pid, &status, 0);

				if (WIFSIGNALED(status))
				{
					// e.g. user hit Ctrl+C => child died to SIGINT => exit code = 130
					g_exit_status = 128 + WTERMSIG(status); // Typically 130
					// Here you can choose how to handle it in the parent:
					//   e.g. skip executing the command (like real shells do)
					//   Or just keep going. Usually we skip further execution.
					//   So you might do something like:
					get_info()->flag = 0; // Indicate “stop this command entirely”
				}
				else if (WIFEXITED(status))
				{
					g_exit_status = WEXITSTATUS(status);
				}
				// The read end of the pipe is the heredoc data
				info->heredoc_fd = pipefd[0];
			}
		}
		else if (type == RED_FO || type == RED_TO || type == DGREAT)
		{
			redir_info = gc_alloc(sizeof(t_redir_info));
			redir_info->type = type;
			redir_info->filename = env_expander(get_filename(node));  // kinda hardcoded
			ft_lstadd_back(&info->redir_list, ft_lstnew(redir_info)); // switch to gc
		}
		return;
	}
	i = 0;
	while (i < node->child_count)
	{
		gather_redirects(node->children[i], info);
		i++;
	}
}

void apply_normal_redirections(t_list *normal_redirects)
{
	t_redir_info *redir_info;
	int fd;

	while (normal_redirects)
	{
		redir_info = normal_redirects->content;
		fd = -1;
		if (redir_info->type == RED_FO) //<
			fd = open(redir_info->filename, O_RDONLY);
		else if (redir_info->type == RED_TO) //>
			fd = open(redir_info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (redir_info->type == DGREAT) //>>
			fd = open(redir_info->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror(redir_info->filename);
			// return ; //or exit?
			exit(1); // is this the correct exit code?
		}
		if (redir_info->type == RED_FO)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		normal_redirects = normal_redirects->next;
	}
}
