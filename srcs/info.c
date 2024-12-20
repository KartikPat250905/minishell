/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 10:27:05 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/16 10:27:31 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_info(t_info *info)
{
	t_info	*info_ptr;

	info_ptr = get_info();
	*info_ptr = *info;
}

void	set_debug(bool	debug)
{
	t_info	*info;

	info = get_info();
	info->debug = debug;
}

//getters
t_info	*get_info(void)
{
	static t_info	info;

	return (&info);
}

bool	get_debug(void)
{
	t_info	*info;

	info = get_info();
	return (info->debug);
}

t_env	*get_env_list(void)
{
	t_info	*info;

	info = get_info();
	return (info->env);
}

char	**get_envp(void)
{
	t_info	*info;

	info = get_info();
	return (info->envp);
}