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
