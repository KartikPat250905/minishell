/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 13:09:34 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/23 13:10:35 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

static void	toggle_quotes(char c, int *in_sq, int *in_dq)
{
	if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
	else if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
}

static char	*append_char(char *pre, char c)
{
	char	single_char[2];
	char	*tmp;

	single_char[0] = c;
	single_char[1] = '\0';
	tmp = gc_strjoin(pre, single_char);
	gc_free(pre);
	return (tmp);
}

static char	*expand_exit_status(char *pre)
{
	char	*exit_code_str;
	char	*tmp;

	exit_code_str = ft_itoa(g_exit_status);
	tmp = gc_strjoin(pre, exit_code_str);
	gc_free(pre);
	gc_free(exit_code_str);
	return (tmp);
}

static char	*expand_env_var(char *pre, char *str, int *i)
{
	char	*env_var;
	char	*value;
	char	*tmp;
	int		start;

	start = *i + 1;
	*i += 1;
	while (ft_isalnum(str[*i]) || str[*i] == '_')
		(*i)++;
	env_var = gc_substr(str, start, *i - start);
	value = get_env(env_var);
	gc_free(env_var);
	if (value)
	{
		tmp = gc_strjoin(pre, value);
		gc_free(pre);
		gc_free(value);
		pre = tmp;
	}
	return (pre);
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
		if ((str[i] == '"' && !in_sq) || (str[i] == '\'' && !in_dq))
		{
			toggle_quotes(str[i], &in_sq, &in_dq);
			i++;
			continue ;
		}
		if (str[i] == '$' && !in_sq)
		{
			if (str[i + 1] == '?')
			{
				pre = expand_exit_status(pre);
				i += 2;
				continue ;
			}
			else if ((str[i + 1] == '_' || ft_isalpha(str[i + 1])))
			{
				pre = expand_env_var(pre, str, &i);
				continue ;
			}
		}
		pre = append_char(pre, str[i]);
		i++;
	}
	return (pre);
}
