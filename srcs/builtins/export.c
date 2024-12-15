# include "minishell.h"

int	ft_count_nodes(t_env *env)
{
	int	result;

	result = 0;
	while (env)
	{
		result++;
		env = env -> next;
	}
	return (result);
}

char	**sort_list(t_env *env)
{
	char	**strings;
	int		i;
	int		flag;
	char	*temp;

	strings = gc_alloc(sizeof(char*) * ft_count_nodes(env) + 1);
	i = 0;
	flag = 1;
	while (env)
	{
		strings[i++] = gc_strdup(env -> key);
		env = env -> next;
	}
	strings[i] = NULL;
	while (flag)
	{
		i = 0;
		flag = 0;
		while (strings[i])
		{
			if (strings[i + 1] && ft_strcmp(strings[i], strings[i + 1]) > 0)
			{
				flag = 1;
				temp = strings[i];
				strings[i] = strings[i + 1];
				strings[i + 1] = temp;
			}
			i++;
		}
	}
	return (strings);
}


void	print_exported(t_env *env)
{
	t_env	*copy;
	char	**array;
	int		i;

	i = 0;
	copy = env;
	array = sort_list(copy);
	while (array[i])
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(array[i], 1);
		if (get_env(array[i]) && get_env(array[i])[0] != '\0')
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(get_env(array[i]), 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putchar_fd('\n', 1);
		/*if (copy -> is_env)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(copy->key, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(copy->value, 1);
			ft_putstr_fd("\"", 1);
			ft_putchar_fd('\n', 1);
		}
		copy = copy -> next;*/
		i++;
	}
	gc_free_array(ft_count_nodes(copy), (void *)array);
}

void	assign_env(char **str)
{
	t_env	*global;

	global = g_env;
	while(global)
	{
		global -> envp = str;
		global = global -> next;
	}
}

void	update_envp(void)
{
	t_env	*global;
	char	**env_new;
	int		i;
	char	*temp;

	global = g_env;
	env_new = gc_alloc(sizeof(char*) * ft_count_pointers(global->envp));
	i = 0;
	while (global)
	{
		temp = gc_strjoin(global->key, "=");
		env_new[i++] = gc_strjoin(temp, global->value);
		global = global -> next;
	}
	global = g_env;
	gc_free_array(ft_count_pointers(global->envp), (void**)global -> envp);
	assign_env(env_new);
}

void	export_var(char **av)
{
	int		i;
	char	*eq;
	size_t	len;

	i = 1;
	while (av[i])
	{
		if (av[i][0] >= '0' && av[i][0] <= '9')
		{
			printf("minishell: export: `%s': not a valid identifier\n", av[i++]);
			continue;
		}
		eq = ft_strchr(av[i], '=');
		if (!eq)
		{
			add_to_env_list(gc_strdup(av[i]), gc_strdup(""), 1);
			i++;
			continue ;
		}
		len = eq - av[i];
		add_to_env_list(gc_strndup(av[i], len), gc_strdup(eq + 1), 1);
		i++;
	}
	update_envp();
}

int	ft_export(char **av)
{
	t_env	*global;

	global = g_env;
	if (ft_strcmp(av[0], "export"))
		return (0);
	if (!av[1])
		print_exported(global);
	else
		export_var(av);
	return (0);
}
