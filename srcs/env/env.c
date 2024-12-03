# include "minishell.h"

int	add_to_env_list(char *key, char *value, int is_env)
{
	t_env	*new;
	t_env	*temp;

	if (!is_key_in_env(key))
	{
		temp = g_env;
		while (temp)
		{	
			if (!ft_strcmp(temp -> key, key))
				temp -> value = value;
			temp = temp -> next;
		}
		return (0);
	}
	new = gc_alloc(sizeof(t_env));
	if (!new)
		return (1);
	new -> key = key;
	new -> value = value;
	new -> is_env = is_env;
	new -> next = NULL;
	envadd(&g_env, new);
	return (0);
}

t_env	*init_env_node(char *env, int if_env)
{
	t_env	*node;
	char	*key;
	char	*value;

	node = gc_alloc(sizeof(t_env));
	if (!node)
		return (NULL);
	key = ft_substr(env, 0, ft_strchr(env, '=') - env);
	value = ft_substr(env, ft_strchr(env, '=') - env + 1, ft_strlen(env) - (ft_strchr(env, '=') - env) - 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		free(env);
		return (NULL);
	}
	node -> key = key;
	node -> value = value;
	node -> is_env = if_env;
	node -> next = NULL;
	return (node);
}

void	envadd(t_env **lst, t_env *new)
{
	t_env	*current;

	if (!(*lst))
	{
		(*lst) = new;
		return ;
	}
	current = (*lst);
	while (current->next != NULL)
		current = current->next;
	current->next = new;
}

t_env	*fetch_envp(char **envp)
{
	int		i;
	t_env	*result;
	t_env	*temp;

	i = 0;
	result = NULL;
	while (envp[i])
	{
		temp = init_env_node(envp[i], 1);
		if (!temp)
			return (NULL);
		envadd(&result, temp);
		i++;
	}
	return (result);
}