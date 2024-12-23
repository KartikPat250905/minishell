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

void	handle_heredoc(char *end_word, t_exec_info *info)
{
	int pipefd[2];
	pid_t hd_pid;
	char *line;
	int status;
	
	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return;
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
	{
		close(pipefd[0]);
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
		exit(0);
	}
	else
	{
		close(pipefd[1]);
		waitpid(hd_pid, &status, 0);
		if (WIFSIGNALED(status))
		{
			g_exit_status = 128 + WTERMSIG(status);
			get_info()->flag = 0;
		}
		else if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		info->heredoc_fd = pipefd[0];
	}
}

void add_redirection_info(int type, char *filename, t_exec_info *info)
{
	t_redir_info *redir_info;

	redir_info = gc_alloc(sizeof(t_redir_info));
	redir_info->type = type;
	redir_info->filename = env_expander(filename);
	ft_lstadd_back(&info->redir_list, ft_lstnew(redir_info));
}

void gather_redirects(t_ast_node *node, t_exec_info *info)
{
	int type;
	int i;

	if (!node)
		return;

	if (node->type == IO_REDIRECT)
	{
		type = get_redirect_type(node);
		if (type == DLESS) // <<
			handle_heredoc(get_here_end_word(node), info);
		else if (type == RED_FO || type == RED_TO || type == DGREAT)
			add_redirection_info(type, get_filename(node), info);
		return ;
	}
	i = 0;
	while (i < node->child_count)
	{
		gather_redirects(node->children[i], info);
		i++;
	}
}

int	open_redirection(t_redir_info *redir_info)
{
	int fd;

	fd = -1;
	if (redir_info->type == RED_FO)
		fd = open(redir_info->filename, O_RDONLY);
	else if (redir_info->type == RED_TO)
		fd = open(redir_info->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redir_info->type == DGREAT)
		fd = open(redir_info->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		perror(redir_info->filename);
	return (fd);
}

int	apply_normal_redirections(t_list *normal_redirects)
{
	t_redir_info *redir_info;
	int			fd;

	while (normal_redirects)
	{
		redir_info = normal_redirects->content;
		fd = open_redirection(redir_info);
		if (fd < 0)
		{
			g_exit_status = EXIT_FAILURE;
			return (g_exit_status);
		}
		if (redir_info->type == RED_FO)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		normal_redirects = normal_redirects->next;
	}
	return (0);
}

void apply_normal_redirections_piped(t_list *normal_redirects)
{
	t_redir_info *redir_info;
	int			fd;

	while (normal_redirects)
	{
		redir_info = normal_redirects->content;
		fd = open_redirection(redir_info);
		if (fd < 0)
		{
			exit(1); //is this the correct exit code? //return?
		}
		if (redir_info->type == RED_FO)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		normal_redirects = normal_redirects->next;
	}
}
