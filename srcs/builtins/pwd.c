/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:27:32 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 15:27:34 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[0] && argv[1])
	{
		printf("minishell: pwd: too many arguments\n");
		return (1);
	}
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("getcwd");
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	add_to_env_list(ft_strdup("PWD"), pwd, 0);
	return (0);
}
