/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: karpatel <karpatel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 11:43:18 by karpatel          #+#    #+#             */
/*   Updated: 2024/12/25 11:43:19 by karpatel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# include "env.h"

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
void	ft_exit(char **av);

void	free_str_array(char **str);
void	update_envp(void);
void	export_var(char **av);
char	**populate_strings(t_env *env);
int		ft_count_nodes(t_env *env);

char	**ft_split(char const *s, char c, int *n);
int		ft_strcmp(const char *s1, const char *s2);
#endif
