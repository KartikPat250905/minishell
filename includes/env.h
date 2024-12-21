#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			**envp;
	char			*key;
	char			*value;
	int				is_env;
	struct s_env	*next;
}			t_env;

void	fetch_envp(char **envp);
char	*get_env(char *key);
void	envadd(t_env **lst, t_env *new);
int		add_to_env_list(char *key, char *value, int is_env);
int		is_key_in_env(char *key);
void	env_to_envp_print(void);
void	add_if_key_exists(char *key, char *value);

#endif
