# include "minishell.h"

int	ft_env(char **av)
{
	if (ft_strcmp("env", av[0]))
		return (0);
	if (av[0] && av[1])
	{
		printf("minishell: env: Arguments and options aren't supported\n");
		return (1);
	}
	env_to_envp_print();
	return (0);
}
