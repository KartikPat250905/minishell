# include "minishell.h"

int	ft_isnumstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!((str[i] >= '0' && str[i] <= '9')))
			return (1);
		i++;
	}
	return (0);
}

int	get_exit_code(char **av)
{
	int	exit_code;

	exit_code = ft_atoi(av[1]);
	if (exit_code < 0)
	{
		exit_code = (exit_code + 256) % 256;
	}
	else if (exit_code > 0)
	{
		exit_code = exit_code % 256;
	}
	else
		exit_code = 0;
	return (exit_code);
}

int	ft_exit(char **av)
{
	int	exit_code;

	if (av[0] && av[1] && av[2])
	{
		printf("minishell: exit: too many arguments\n");
		return (1);
	}
	if (av[0] && !av[1])
		exit_code = 0;
	else if ((av[1][0] == '+' || av[1][0] == '-' || ft_isdigit(av[1][0])))
	{
		exit_code = get_exit_code(av);
	}
	else
	{
		printf("minishell: exit: numeric argument required\n");
		return (1);
	}
	//gc_free_all();
	g_exit_status = exit_code;
	exit(exit_code);
	return (0);
}
