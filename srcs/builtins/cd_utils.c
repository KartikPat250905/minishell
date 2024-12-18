/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:26:33 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 15:26:35 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_char_pointer(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		i++;
	}
	return (i);
}

char	*build_path_env(char *input)
{
	char	*try_path;
	char	**cd_path;
	int		cur;
	int		i;

	cur = 0;
	if (!get_env("CDPATH"))
		return (ft_strdup(input));
	cd_path = ft_split(input, ':', &i);
	while (cur < i)
	{
		try_path = ft_strjoin(cd_path[cur], input);
		if (access(try_path, F_OK | R_OK) == 0)
		{
			gc_free_array(count_char_pointer(cd_path), (void **)cd_path);
			return (try_path);
		}
		free(try_path);
		cur++;
	}
	gc_free_array(count_char_pointer(cd_path), (void **)cd_path);
	return (ft_strdup(input));
}
