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

// char	*join_with_slashes(char *p1, char *p2)
// {
// 	char	*result;
// 	char	*temp;

// 	temp = ft_strjoin("/", p2);
// 	if (!temp)
// 		return (NULL);
// 	result = ft_strjoin(p1, temp);
// 	if (!result)
// 		return (NULL);
// 	return (result);
// }

// char	*build_path(char *av)
// {
// 	char	*path;
// 	char	*temp;

// 	if (av[0] == '/')
// 		path = ft_strdup(av);
// 	else if(!ft_strncmp(".", av, 1) || !ft_strncmp("..", av, 2))
// 		path = join_with_slashes(get_env("PWD") ,av);
// 	else
// 	{
// 		path = build_path_env(av);
// 		if (ft_strcmp(path, av))
// 		{
// 			temp = path;
// 			path = join_with_slashes(get_env("PATH"), path);
// 			free(temp);
// 		}
// 	}
// 	return (path);
// }

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
		printf("CD getting this: %s\n", av[1]);
		path = av[1];
		if (chdir(path) == ERROR)
		{
			perror("minishell: cd:");
			return (1);
		}
		add_to_env_list("OLDPWD", get_env("PWD"), 0);
		cwd = getcwd(NULL, 0);
		if (!cwd)
		{
			perror("minishell: cd: getcwd failed");
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
