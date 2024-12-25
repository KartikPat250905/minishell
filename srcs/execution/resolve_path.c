/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolve_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 19:24:54 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 19:24:59 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

int	is_cmd_already_path(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0)
			return (1);
		else
		{
			ft_putstr_fd("./microshell: ", STDERR_FILENO);
			perror(cmd);
			gc_free_all();
			free_env_list();
			exit(EXIT_CMD_NOT_FOUND);
		}
	}
	return (0);
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
	return (NULL);
}

void	child_exit(char **argv, char *path)
{
	if (!path)
	{
		ft_putstr_fd(argv[0], 2);
		ft_putendl_fd(": command not found", 2);
		g_exit_status = 127;
		gc_free_all();
		free_env_list();
		exit(g_exit_status);
	}
	if (execve(path, argv, get_info()->envp) == -1)
	{
		perror("execve");
		g_exit_status = 126;
		gc_free_all();
		free_env_list();
		exit(g_exit_status);
	}
}

//check if directory
void	resolve_and_exec_cmd(char **argv)
{
	char	*path;
	char	**paths;
	int		n;

	path = get_env("PATH");
	if (is_cmd_already_path(argv[0]))
		path = argv[0];
	else
	{
		if (!path)
		{
			ft_putstr_fd("microshell: ", 2);
			ft_putstr_fd(argv[0], 2);
			ft_putendl_fd(": No such file or directory", 2);
			g_exit_status = 127;
			gc_free_all();
			free_env_list();
			exit(g_exit_status);
		}
		paths = gc_split(path, ':', &n);
		path = look_for_cmd(argv[0], paths);
		gc_free_array(n, (void **)paths);
	}
	child_exit(argv, path);
}
