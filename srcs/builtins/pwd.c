# include "minishell.h"

int	ft_pwd(char **argv)
{
	char	*pwd;

	if (argv[0] && argv[1])
		return (1);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (1);
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}
