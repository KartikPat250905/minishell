# include "minishell.h"

int	ft_env(char **av)
{
	if (av[0] && av[1])
		return (0);
	if (ft_strcmp("env", av[0]))
		return (1);
	env_to_envp_print();
	return (0);
}
