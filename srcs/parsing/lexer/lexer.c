/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:46:07 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/05 13:47:33 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/*
 * Hardcored lexer just to be able to test the LR parsing algo,
 * we obviously need a proper lexer that takes the original raw string
 * and returns a stack of input tokens, remember,
 * we are reading from left to right, so we fill the stack from right to left
 *
 * test case:
 * ls > outfile EOF
 * WORD RET_TO WORD EOF
 *
 * btw, should prototype be?
 * int lexer(char *str, t_stack *input_tokens);
 *
 * or
 *
 * t_stack *lexer(char *str);
 */
void	lexer(t_stack *tokens)
{
	tokens = init_stack();
	//if (!input_tokens)
	push(tokens, init_node(END)); //EOF
	push(tokens, init_node(WORD)); //outfile
	//if (!init_node(WORD))
	push(tokens, init_node(RED_TO)); //>
	push(tokens, init_node(WORD)); //ls
}
