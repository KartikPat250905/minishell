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

void	assign_env(char **str)
{
	t_env	*global;

	global = g_env;
	while (global)
	{
		global -> envp = str;
		global = global -> next;
	}
}

void	update_envp(void)
{
	t_env	*global;
	char	**env_new;
	int		i;
	char	*temp;

	global = g_env;
	env_new = gc_alloc(sizeof(char *) * ft_count_pointers(global->envp));
	i = 0;
	while (global)
	{
		temp = gc_strjoin(global->key, "=");
		env_new[i++] = gc_strjoin(temp, global->value);
		global = global -> next;
	}
	global = g_env;
	gc_free_array(ft_count_pointers(global->envp), (void **)global -> envp);
	assign_env(env_new);
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
			printf("minishell: export: `%s': not a valid identifier\n", av[i++]);
			continue ;
		}
		eq = ft_strchr(av[i], '=');
		if (!eq)
		{
			add_to_env_list(gc_strdup(av[i]), gc_strdup(""), 1);
			i++;
			continue ;
		}
		len = eq - av[i];
		add_to_env_list(gc_strndup(av[i], len), gc_strdup(eq + 1), 1);
		i++;
	}
	update_envp();
}
