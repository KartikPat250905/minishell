/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:09:34 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/23 16:49:46 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

char	*append_char(char *pre, char c)
{
	char	single_char[2];
	char	*tmp;

	single_char[0] = c;
	single_char[1] = '\0';
	tmp = gc_strjoin(pre, single_char);
	gc_free(pre);
	return (tmp);
}

char	*env_expander(char *str)
{
	char	*pre;
	int		in_sq;
	int		in_dq;
	int		i;

	pre = gc_strdup("");
	in_sq = 0;
	in_dq = 0;
	i = 0;
	while (str[i])
	{
		if (is_quote(str[i], &in_sq, &in_dq))
		{
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_sq)
		{
			if (handle_expansion(&pre, str, &i))
				continue ;
		}
		pre = append_char(pre, str[i]);
		i++;
	}
	return (pre);
}
