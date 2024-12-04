# include "minishell.h"

int	ft_export(int ac, char **av)
{
	t_env	*env;

	env = g_env;
	if (ft_strcmp(av[0], "export") || ac > 1)
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