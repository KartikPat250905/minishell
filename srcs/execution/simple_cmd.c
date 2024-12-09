/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 10:53:03 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/06 10:53:11 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

int	get_redirect_type(t_ast_node *io_redirect_node)
{
	t_ast_node	*child;
	t_ast_node	*op_node;
	
	child = io_redirect_node->children[0];
	if (child->type == IO_FILE)
	{
		op_node = child->children[0];
		if (op_node->token->type == RED_FO)
			return (RED_FO);
		else if (op_node->token->type == RED_TO)
			return (RED_TO);
		else if (op_node->token->type == DGREAT)
			return (DGREAT);
	}
	else if (child->type == IO_HERE)
	{
		//return (HERE_END);
		return (DLESS); //not sure if this is correct
		//this needs a implementation for here_doc
	}
	return (-1);
}

char	*get_filename(t_ast_node *io_redirect_node)
{
	t_ast_node	*child;
	t_ast_node	*filename;
	t_ast_node	*here_end;
	t_ast_node	*word;
	
	child = io_redirect_node->children[0];
	if (child->type == IO_FILE)
	{
		filename = child->children[1];
		word = filename->children[0];
		return (word->token->value);
	}
	else if (child->type == IO_HERE)
	{
		here_end = child->children[1];
		word = here_end->children[0];
		return (word->token->value);
	}
	return (NULL);
}

void	handle_io_redirect(t_ast_node *io_redirect_node)
{
	char	*filename;
	int		redirect_type;
	int		fd;
	
	fd = 0;
	filename = get_filename(io_redirect_node);
	redirect_type = get_redirect_type(io_redirect_node);

	if (redirect_type == RED_FO)
		fd = open(filename, O_RDONLY);
	else if (redirect_type == RED_TO)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (redirect_type == DGREAT)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(filename);
		return ;
	}
	if (redirect_type == RED_FO)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	apply_redirections(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	
	if (node->type == IO_REDIRECT)
	{
		handle_io_redirect(node);
		return ;
	}
	i = 0;
	while (i < node->child_count)
	{
		//io_redirects only have 1 child
		apply_redirections(node->children[i]);
		i++;
	}
}

void	construct_cmd(t_ast_node *node, t_list **words)
{
	t_list	*cmd_elem;
	int		i;

	if (!node)
		return ;

	if (node->type == IO_REDIRECT || node->type == IO_FILE || node->type == IO_HERE || node->type == FILENAME)// || node->type == HERE_END)
		return ;

	if (node->type == WORD)
	{
		cmd_elem = ft_lstnew(node->token->value);
		//if (!cmd_elem)
		ft_lstadd_back(words, cmd_elem); //convert to gc_lstadd_back
		return ;
	}
	i = 0;
	while (i < node->child_count)
	{
		construct_cmd(node->children[i], words);
		i++;
	}
}

char	**build_argv(t_ast_node *simple_command)
{
	t_list	*words;
	t_list	*tmp;
	int		i;
	char	**argv;

	i = 0;
	words = NULL;
	construct_cmd(simple_command, &words);
	tmp = words;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	argv = gc_alloc(sizeof(char *) * (i + 1));
	if (!argv)
	{
		//free words linked list
		return (NULL);
	}
	i = 0;
	while (words)
	{
		argv[i] = words->content;
		i++;
		words = words->next;
	}
	argv[i] = NULL;
	//free words linked list
	printf("words linked list:\n");
	i = 0;
	while (argv[i])
	{
		printf("%s\n", argv[i]);
		i++;
	}
	return (argv);
}

char	*look_for_cmd(char *cmd, char **paths)
{
	int		i;
	char	*aux;
	char	*triable_path;

	i = 0;
	while (paths[i])
	{
		aux = gc_strjoin(paths[i], "/");
		triable_path = gc_strjoin(aux, cmd);
		if (access(triable_path, F_OK | X_OK) == 0)
			return (triable_path);
		i++;
	}
	ft_putstr_fd("./microshell: ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	//gc_free_all(); //possible due to being in a child process?
	//exit(EXIT_CMD_NOT_FOUND);
	return (NULL);
}

void	execute_simple_cmd(t_ast_node *node)
{
	char	**argv;
	pid_t	pid;
	char	*path;
	char	**paths;
	int		status;
	int		n;

	/*if (is_builtin(node))
	{
		execute_builtin(node);
		return ;
	}*/
	argv = build_argv(node);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return ; //not sure if we should return or exit
	}
	else if (pid == 0) //child
	{
		apply_redirections(node);
		path = get_env("PATH");
		if (!path)
		{
			ft_putendl_fd("minishell: command not found", 2);
			exit(127);
		}
		paths = gc_split(path, ':', &n);
		path = look_for_cmd(argv[0], paths);
		execve(path, argv, g_env->envp);
		perror("execve");
		exit(126); //not sure if this is the correct exit code
	}
	else
	{
		waitpid(pid, &status, 0);
	}
	//gc_free_array((void **)argv, //length of argv);
}
