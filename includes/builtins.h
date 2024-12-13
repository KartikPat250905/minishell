#ifndef BUILTINS_H
# define BUILTINS_H

char	*build_path_env(char *input);

typedef struct s_builtin_iterators
{
	int	start;
	int	end;
	int	len;
	int	i;
}				t_bt;

typedef struct s_snode
{
	char			*string;
	struct s_snode	*next;
}	t_snode;

typedef struct s_sstack
{
	t_snode	*top;
	size_t	size;
}	t_sstack;

int		ft_pwd(char **argv);
int		ft_cd(char **av);
int		ft_echo(char **av);
int		ft_env(char **av);
int		ft_export(char **av);
int		ft_unset(char **av);
int		ft_exit(char **av);

void	spush(t_sstack *stack, t_snode *node);
t_snode	*spop(t_sstack *stack);
t_snode	*sinit_node(char *value);
t_sstack	*sinit_stack(void);
void	free_str_array(char **str);
void	update_envp(void);

char	**ft_split(char const *s, char c, int *n);
int		ft_strcmp(const char *s1, const char *s2);
#endif
