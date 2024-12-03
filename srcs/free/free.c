# include "minishell.h"

void	free_str_array(char **str)
{
	char	**begin;

	if (str)
	{
		begin = str;
		while (*str)
		{
			free(*str);
			++str;
		}
		free(begin);
	}
}