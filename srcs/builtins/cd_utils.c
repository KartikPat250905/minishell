# include "minishell.h"

char	*build_path_env(char *input)
{
	char	*try_path;
	char	**cd_path;
	int		cur;
	int		i;

	cur = 0;
	if (!get_env("CDPATH"))
		return (ft_strdup(input));
	cd_path = ft_split(input, ':', &i);
	while (cur < i)
	{
		try_path = ft_strjoin(cd_path[cur], input);
		if (access(try_path, F_OK | R_OK) == 0)
		{
			free_str_array(cd_path);
			return (try_path);
		}
		free(try_path);
		cur++;
	}
	free_str_array(cd_path);
	return (ft_strdup(input));
}