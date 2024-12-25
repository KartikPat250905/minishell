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

void	add_redirection_info(int type, char *filename, t_exec_info *info)
{
	t_redir_info	*redir_info;

	redir_info = gc_alloc(sizeof(t_redir_info));
	redir_info->type = type;
	redir_info->filename = env_expander(filename);
	ft_lstadd_back(&info->redir_list, gc_lstnew(redir_info));
}

void	gather_redirects(t_ast_node *node, t_exec_info *info)
{
	int	type;
	int	i;

	if (!node)
		return ;
	if (node->type == IO_REDIRECT)
	{
		type = get_redirect_type(node);
		if (type == DLESS)
			handle_heredoc(get_here_end_word(node), info);
		else if (type == RED_FO || type == RED_TO || type == DGREAT)
			add_redirection_info(type, get_filename(node), info);
		return ;
	}
	i = 0;
	while (i < node->child_count && g_exit_status != 130)
	{
		gather_redirects(node->children[i], info);
		i++;
	}
}

int	open_redirection(t_redir_info *redir_info)
{
	int	fd;

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
	t_redir_info	*redir_info;
	int				fd;

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

void	apply_normal_redirections_piped(t_list *normal_redirects)
{
	t_redir_info	*redir_info;
	int				fd;

	while (normal_redirects)
	{
		redir_info = normal_redirects->content;
		fd = open_redirection(redir_info);
		if (fd < 0)
		{
			gc_free_all();
			free_env_list();
			exit(1);
		}
		if (redir_info->type == RED_FO)
			dup2(fd, STDIN_FILENO);
		else
			dup2(fd, STDOUT_FILENO);
		close(fd);
		normal_redirects = normal_redirects->next;
	}
}
