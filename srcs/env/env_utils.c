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

void	env_to_envp_print(void)
{
	t_env	*env;

	env = g_env;
	while (env)
	{
		if (env -> value[0] == '\0')
		{
			env = env -> next;
			continue ;
		}
		ft_putstr_fd(env->key, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(env ->value, 1);
		ft_putchar_fd('\n', 1);
		env = env->next;
	}
}
