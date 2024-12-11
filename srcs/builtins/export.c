# include "minishell.h"

/*void	sort_list(t_env *env)
{
	t_env	*temp;
	int		flag;
	t_env	*cur;
	t_env	*next;
	t_env	*prev;

	temp = env;
	flag = 1;
	prev = NULL;
	while (flag)
	{
		while (temp)
		{
			cur = temp;
			next = temp -> next;
			if (ft_strcmp(cur -> key, next -> key) < 0)
			{
				prev -> next =
			}
			temp = temp -> next -> next;
		}
		temp = env;
	}
}*/

int	ft_export(char **av)
{
	t_env	*env;
	t_env	*global;

	global = g_env;
	env = fetch_envp(global -> envp);
	//sort_list(env);
	if (ft_strcmp(av[0], "export") || av[2])
		return (1);
	while (env)
	{
		if (env -> is_env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(env->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(env->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putchar_fd('\n', 1);
		}
		env = env -> next;
	}
	return (0);
}
