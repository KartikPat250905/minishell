/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 20:47:34 by aapadill          #+#    #+#             */
/*   Updated: 2024/12/23 21:00:07 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"
#include "execution.h"

void	toggle_quotes(char c, int *in_sq, int *in_dq)
{
	if (c == '"' && !(*in_sq))
		*in_dq = !(*in_dq);
	else if (c == '\'' && !(*in_dq))
		*in_sq = !(*in_sq);
}

int	is_quote(char c, int *in_sq, int *in_dq)
{
	if (c == '"' || c == '\'')
	{
		toggle_quotes(c, in_sq, in_dq);
		return (1);
	}
	return (0);
}

char	*expand_exit_status(char *pre)
{
	char	*exit_code_str;
	char	*tmp;

	exit_code_str = gc_itoa(g_exit_status);
	tmp = gc_strjoin(pre, exit_code_str);
	gc_free(pre);
	gc_free(exit_code_str);
	return (tmp);
}

char	*expand_env_var(char *pre, char *str, int *i)
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

int	handle_expansion(char **pre, char *str, int *i)
{
	if (str[*i + 1] == '?')
	{
		*pre = expand_exit_status(*pre);
		*i += 2;
		return (1);
	}
	else if (str[*i + 1] == '_' || ft_isalpha(str[*i + 1]))
	{
		*pre = expand_env_var(*pre, str, i);
		return (1);
	}
	return (0);
}


