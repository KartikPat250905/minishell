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

void	free_and_exit(void)
{
	gc_free_all();
	free_env_list();
	exit(EXIT_FAILURE);
}

void	free_and_exit_with(int exit_code)
{
	gc_free_all();
	free_env_list();
	exit(exit_code);
}