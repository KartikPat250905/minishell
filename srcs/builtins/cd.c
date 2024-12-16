# include "minishell.h"

int	go_home(void)
{
	char	*home_path;

	home_path = get_env("HOME");
	if (!home_path)
	{
		ft_putstr_fd("microshell: cd: error: HOME in undefined in PATH\n", 2);
		return (1);
	}
	else
	{
		if (chdir(home_path) == ERROR)
		{
			perror("minishell: cd:");
			return (1);
		}
	}
	add_to_env_list("OLDPWD", get_env("PWD"), 0);
	add_to_env_list("PWD", home_path, 1);
	return (0);
}

int	ft_cd(char **av)
{
	char	*path;
	char	*cwd;

	if (ft_strcmp("cd", av[0]))
		return (0);
	if (!av[1])
		return (!go_home());
	else if (av[0] && av[1] && !av[2])
	{
		path = av[1];
		if (chdir(path) == -1)
		{
			printf("bash: cd: %s: No such file or directory\n", av[1]);
			return (1);
		}
		add_to_env_list("OLDPWD", get_env("PWD"), 0);
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			printf("minishell: cd: getcwd failed\n");
			return (1);
		}
		add_to_env_list("PWD", gc_strdup(cwd), 1);
		free(cwd);
	}
	else
	{
		printf("minishell: cd: too many arguments\n");
		return (1);
	}
	return (0);
}
