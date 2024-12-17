/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 15:27:06 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 15:27:07 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_nodes(t_env *env)
{
	int	result;

	result = 0;
	while (env)
	{
		result++;
		env = env -> next;
	}
	return (result);
}

char	**sort_list(t_env *env)
{
	char	**strings;
	int		i;
	int		flag;
	char	*temp;

	flag = 1;
	strings = populate_strings(env);
	while (flag)
	{
		i = 0;
		flag = 0;
		while (strings[i])
		{
			if (strings[i + 1] && ft_strcmp(strings[i], strings[i + 1]) > 0)
			{
				flag = 1;
				temp = strings[i];
				strings[i] = strings[i + 1];
				strings[i + 1] = temp;
			}
			i++;
		}
	}
	return (strings);
}
/*if (copy -> is_env)
{
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(copy->key, 1);
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(copy->value, 1);
	ft_putstr_fd("\"", 1);
	ft_putchar_fd('\n', 1);
}
copy = copy -> next;*/

void	print_exported(t_env *env)
{
	t_env	*copy;
	char	**array;
	int		i;

	i = 0;
	copy = env;
	array = sort_list(copy);
	while (array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[i], 1);
		if (get_env(array[i]) && get_env(array[i])[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(get_env(array[i]), 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
	gc_free_array(ft_count_nodes(copy), (void *)array);
}

int	ft_export(char **av)
{
	t_env	*global;

	global = g_env;
	if (ft_strcmp(av[0], "export"))
		return (0);
	if (!av[1])
		print_exported(global);
	else
		export_var(av);
	return (0);
}
