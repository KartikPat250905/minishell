# include "minishell.h"

void	free_node_unset(char *key)
{
	t_env	*env;
	t_env	*prev;

	env = g_env;
	prev = NULL;
	while (env)
	{
		if (!ft_strcmp(key, env -> key))
			break ;
		prev = env;
		env = env -> next;
	}
	if (!env)
		return ;
	if (prev != NULL)
		prev -> next = env -> next;
	else
		prev->next = env->next;
	env -> next = NULL;
	free(env -> key);
	free(env -> value);
	free(env);
}

void	unset_var(char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		free_node_unset(av[i]);
		i++;
	}
	update_envp();
}
//unset head properly

int	ft_unset(char **av)
{
	if (ft_strcmp("unset", av[0]))
		return (0);
	if (get_env(av[1]) == NULL)
		return (0);
	free_node_unset(av[1]);
	return (0);
}
