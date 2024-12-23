/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utilstwo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:15:53 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 16:15:55 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**populate_strings(t_env *env)
{
	int		i;
	char	**strings;

	i = 0;
	strings = gc_alloc(sizeof(char *) * (ft_count_nodes(env) + 1));
	while (env)
	{
		strings[i++] = gc_strdup(env -> key);
		env = env -> next;
	}
	strings[i] = NULL;
	return (strings);
}
