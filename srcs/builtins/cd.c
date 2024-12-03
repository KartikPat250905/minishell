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
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
        } else {
            printf("Current working directory: %s\n", cwd);
        }
	return (0);
}

char	*join_with_slashes(char *p1, char *p2)
{
	char	*result;
	char	*temp;

	temp = ft_strjoin("/", p2);
	if (!temp)
		return (NULL);
	result = ft_strjoin(p1, temp);
	free(temp);
	if (!result)
		return (NULL);
	return (result);
}

char	*build_path(char *av)
{
	char	*path;
	char	*temp;

	if (av[0] == '/')
		path = ft_strdup(av);
	else if(!ft_strncmp(".", av, 1) || !ft_strncmp("..", av, 2))
		path = join_with_slashes(get_env("PWD") ,av);
	else
	{
		path = build_path_env(av);
		if (ft_strcmp(path, av))
		{
			temp = path;
			path = join_with_slashes(get_env("PATH"), path);
			free(temp);
		}
	}
	return (path);
}

int	ft_cd(int ac, char **av)
{
	char	*path;

	if (ac == 1)
		return (!go_home());
	else
	{
		path = build_path_env(av[1]);
		if (chdir(path) == ERROR)
		{
			perror("minishell: cd:");
			return (1);
		}
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) == NULL) {
            perror("getcwd");
        } else {
            printf("Current working directory: %s\n", cwd);
        }
	}
	return (0);
}