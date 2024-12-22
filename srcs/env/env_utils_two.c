/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 10:16:08 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/22 10:16:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_if_key_exists(char *key, char *value)
{
	t_env	*temp;

	temp = get_info()->env;
	while (temp)
	{
		if (!ft_strcmp(temp -> key, key))
		{
			temp -> value = value;
			return ;
		}
		temp = temp -> next;
	}
}
