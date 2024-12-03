# include "minishell.h"

int	is_key_in_env(char *key)
{
	t_env	*temp;

	temp = g_env;
	while (temp)
	{
		if (!ft_strcmp(temp -> key, key))
			return (0);
		temp = temp -> next;
	}
	return (1);
}

char	*get_env(char *key)
{
	t_env	*env;

	env = g_env;
	while (env)
	{
		if (!ft_strcmp(key, env -> key))
			return (env -> value);
		env = env -> next;
	}
	return (NULL);
}