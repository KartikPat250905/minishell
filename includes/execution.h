/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:19:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/11 10:07:17 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <sys/wait.h>

# define EXIT_CMD_NOT_FOUND 127
# define EXIT_PERMISSION_DENIED 126

typedef struct s_redir_info
{
	int		type;
	char	*filename;
}	t_redir_info;

typedef struct s_exec_info
{
	int		heredoc_fd;
	t_list	*redir_list;
}	t_exec_info;

typedef struct s_pipe_data
{
	int		*pipefds;
	pid_t	*pids;
	int		cmd_count;
	int		pipe_count;
}	t_pipe_data;

//execute.c
bool	is_builtin(char *cmd_name);
int		execute_builtin(char **argv);
void	execute_pipe_seq(t_ast_node *node);
void	execute_ast(t_ast_node *node);

//pipe_sequence.c
void	execute_pipeline(t_ast_node **commands, int cmd_count);

//getters.c
t_ast_node	**get_simple_cmds(t_ast_node *node, int *count);
int			get_redirect_type(t_ast_node *io_redirect_node);
char		*get_filename(t_ast_node *io_redirect_node);
char		*get_here_end_word(t_ast_node *io_redirect);

//redirections.c
void	gather_redirects(t_ast_node *node, t_exec_info *info);
void	apply_normal_redirections(t_list *normal_redirects);
void	apply_normal_redirections_piped(t_list *normal_redirects);

//execution_utils.c
bool	unclosed_quotes(char *str);
char	*env_expander(char *str);
void	construct_cmd(t_ast_node *node, t_list **words);
char	**build_argv(t_ast_node *simple_command);

//resolve_path.c
int		is_cmd_already_path(char *cmd);
char	*look_for_cmd(char *cmd, char **paths);
void	resolve_and_exec_cmd(char **argv);

//simple_cmd_utils.c
void	initialize_exec_info(t_exec_info *info);
void	wait_for_child(pid_t pid);
void	execute_builtin_cmd(char **argv, t_exec_info *info);
void	execute_external_cmd(char **argv, t_exec_info *info);

//simple_cmd.c
void	execute_simple_piped_cmd(char **argv);
void	execute_simple_cmd(t_ast_node *node);

#endif
