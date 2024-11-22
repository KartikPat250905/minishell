/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 12:46:07 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/22 15:11:05 by aapadill         ###   ########.fr       */
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
 * WORD RED_TO WORD EOF
 *
 * ls > > ls
 * WORD RED_TO RED_TO WORD EOF
 *
 * ls | cat EOF
 * WORD PIPE WORD EOF
 *
 * btw, should prototype be?
 * int lexer(char *str, t_stack *input_tokens);
 *
 * or
 *
 * t_stack *lexer(char *str);
 */

//ls < ls ls | cat | ls > outfile
void	lexer(t_stack *tokens)
{
	//if (!input_tokens)
	push(tokens, init_node(END)); //EOF
	push(tokens, init_node(WORD)); //outfile
	push(tokens, init_node(RED_TO)); // >
	push(tokens, init_node(WORD)); //cat
	push(tokens, init_node(PIPE)); // |
	push(tokens, init_node(WORD)); //hello
	push(tokens, init_node(WORD)); //echo
}
