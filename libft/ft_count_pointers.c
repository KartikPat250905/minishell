# include "libft.h"

int	ft_count_pointers(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
		i++;
	return (i);
}