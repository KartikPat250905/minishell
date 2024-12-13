# include "minishell.h"

/*
After checking i found that we might not need it but it is still here in case we need to sort something
void	sort_list(t_env **env)
{
	t_env	*temp;
	int		flag;
	t_env	*cur;
	t_env	*next;
	t_env	*prev;

	flag = 1;
	while (flag)
	{
		flag = 0;
		prev = NULL;
		temp = *env;
		while (temp && temp -> next)
		{
			cur = temp;
			next = temp -> next;
			printf("Current key is %s and the next one is %s\n",cur->key, next -> key);
			if (ft_strcmp(cur -> key, next -> key) < 0)
			{
				if (prev != NULL)
					prev -> next = next;
				else
					*env = next;
				cur -> next = next -> next;
				next -> next = cur;
				prev = next;
				flag = 1;
			}
			else
				prev = cur;
			temp = cur -> next;
		}
	}
}*/

void	print_exported(t_env *env)
{
	while (env)
	{
		printf("\nThe key is %s and the value is %s",env->key,env->value);
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
		eq = ft_strchr(av[i], '=');
		if (!eq)
		{
			add_to_env_list(gc_strdup(av[i]), gc_strdup(""), 1);
			continue ;
		}
		len = eq - av[i];
		add_to_env_list(gc_strndup(av[i], len), gc_strdup(eq), 1);
		i++;
	}
	update_envp();
}

int	ft_export(char **av)
{
	t_env	*env;
	t_env	*global;

	global = g_env;
	env = fetch_envp(global -> envp);
	if (ft_strcmp(av[0], "export"))
		return (0);
	if (!av[1])
		print_exported(env);
	else
		export_var(av);
	return (0);
}
