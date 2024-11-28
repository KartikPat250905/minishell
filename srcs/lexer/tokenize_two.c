/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aapadill <aapadill@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:22:54 by aapadill          #+#    #+#             */
/*   Updated: 2024/11/27 17:22:55 by aapadill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "lexer.h"

void	handle_single_quotes(t_iterators *it, t_token_stack *stack)
{
	t_token_node	*node;

	node = create_token(WORD, gc_strndup(&it->input[it->start + 1], it->cur - it->start - 2));
	node -> state = NORMAL;
	push_token(stack, node);
}

void	handle_double_quotes(t_iterators *it, t_token_stack *stack)
{
	t_token_node	*node;

	node = create_token(WORD, gc_strndup(&it->input[it->start + 1], it->cur - it->start - 2));
	node -> state = DOUBLE_QUOTES;
	push_token(stack, node);
}

bool	tokenize_quotes(t_iterators *it, t_token_stack *stack)
{
	it->start = it->cur;
	if (it->input[it->cur] == '\'' || it->input[it->cur] == '"'
	)
	{
		it->quote_char = it->input[it->cur];
		it->cur++;

		while (it->cur < it->len && it->input[it->cur] != it->quote_char)
			it->cur++;
		it->cur++;
		// Create token based on quote type
		if (it->quote_char == '\'')
			handle_single_quotes(it, stack);
		else
			handle_double_quotes(it, stack);
		return (true);
	}
	return (false);
}


bool	tokenize_words(t_iterators *it, t_token_stack *stack)
{
	t_token_node	*node;
	char			*word;

	it->start = it->cur;
	if (is_token(it->input[it->cur], it->input[it->cur + 1]))
		return (false);
	while (it->cur < it->len && it->input[it->cur] != ' ' && !is_token(it->input[it->cur], it->input[it->cur + 1]))
		it->cur++;
	word = gc_strndup(&it->input[it->start], it->cur - it->start);
	node = create_token(WORD, word);
	push_token(stack, node);
	return (true);
}
