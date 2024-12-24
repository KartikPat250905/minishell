/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:27:26 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 15:27:27 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnumstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

int	get_exit_code(char **av)
{
	int	exit_code;

	exit_code = ft_atoi(av[1]);
	if (exit_code < 0)
	{
		exit_code = (exit_code + 256) % 256;
	}
	else if (exit_code > 0)
	{
		exit_code = exit_code % 256;
	}
	else
		exit_code = 0;
	return (exit_code);
}

void	ft_exit(char **av)
{
	int	exit_code;

	exit_code = 2;
	if (av[0] && !av[1])
		exit_code = 0;
	else if ((av[1][0] == '+' || av[1][0] == '-' || ft_isdigit(av[1][0])) && !av[1])
	{
		exit_code = get_exit_code(av);
		if ((ft_strlen(av[1]) > 19 && av[1][0] != '-') ||
			(ft_strlen(av[1]) > 19 && av[1][0] == '-'))
			printf("minishell: exit: numeric argument required\n");
	}
	else if (av[1] && av[2])
	{
		exit_code = 1;
		printf("minishell: exit: too many arguments.\n");
	}
	else
		printf("minishell: exit: numeric argument required\n");
	g_exit_status = exit_code;
	printf("exit\n");
	free_env_list();
	gc_free_all();
	exit(exit_code);
}
