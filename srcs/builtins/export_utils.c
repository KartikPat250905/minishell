/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 16:05:01 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/17 16:05:02 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_envp(void)
{
	t_env	*global;
	char	**env_new;
	int		i;
	char	*temp;

	i = 0;
	global = get_info()->env;
	while (global)
	{
		i++;
		global = global->next;
	}
	env_new = gc_alloc(sizeof(char *) * (i + 1));
	i = 0;
	global = get_info()->env;
	while (global)
	{
		temp = gc_strjoin(global->key, "=");
		env_new[i++] = gc_strjoin(temp, global->value);
		global = global -> next;
	}
	env_new[i] = NULL;
	//if (get_info()->envp)
	//	gc_free_array(i, (void **)(get_info()->envp));
	get_info()->envp = env_new;
}

int	is_edge(char *str)
{
	int	i;

	i = 0;
	if ((str[0] >= '0' && str[0] <= '9') || str[0] == '-' || str[0] == '=')
		return (1);
	while (str[i])
	{
		if (str[i] == '.' || str[i] == '/' || str[i] == ':')
			return (1);
		if (str[i] == '=')
			break ;
		i++;
	}
	return (0);
}

void	export_var(char **av)
{
	int		i;
	char	*eq;
	size_t	len;

	i = 1;
	while (av[i])
	{
		if (is_edge(av[i]))
		{
			printf("minishell: export: `%s':"
				"not a valid identifier\n", av[i++]);
			g_exit_status = 1;
			continue ;
		}
		eq = ft_strchr(av[i], '=');
		if (!eq)
		{
			add_to_env_list(ft_strdup(av[i]), ft_strdup(""), 1);
			i++;
			continue ;
		}
		len = eq - av[i];
		add_to_env_list(ft_strndup(av[i++], len), ft_strdup(eq + 1), 1);
	}
	update_envp();
}
