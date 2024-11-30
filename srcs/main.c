/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:40:50 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/06 13:12:09 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parsing.h"



int	main(void)
{
	char			*input;
	t_token_stack	*tokens;
	int				ret;

	tokens = NULL;
	activate_signal_handler();
	while (1)
	{
		input = readline("microshell> ");
		if (!input)
		{
			printf("Exit\n");
			break ;
		}
		if (!*input)
			continue ;
		if (*input)
			add_history(input);
		tokens = init_token_stack();
		tokens = lexer(input);
		ret = parsing_main(tokens);
		free(input);
		if (ret == 1)
			ft_putendl_fd("-accepted-", 1);
		else
			ft_putendl_fd("-not accepted-", 1);
	}
	return (0);
}
