/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:19:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/07 13:19:21 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_PERMISSION_DENIED 126

typedef	struct s_redir_info
{
	int		type;
	char	*filename;
}	t_redir_info;

typedef struct s_exec_info
{
	int		heredoc_fd;
	t_list	*redir_list;
}	t_exec_info;

void	execute_simple_cmd(t_ast_node *node);
void	execute_ast(t_ast_node *node);

bool	is_builtin(char *cmd_name);
int		execute_builtin(char **argv);
void	execute_pipe_seq(t_ast_node *node);

#endif