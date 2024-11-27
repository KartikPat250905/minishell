# include "lexer.h"

void	handle_space(t_iterators *it)
{
	while (it->input[it->cur] != '\0' && it->input[it->cur] == ' ')
	{
		it->cur++;
	}
}

bool	tokenize_pipe(t_iterators *it, t_token_stack *stack)
{
	t_token_node *new;

	if (it->input[it->cur] == '|')
	{
		new = create_token(PIPE, gc_strdup("|"));
		//if (!new)
		//	ft_exit(); //which cleans the gc and exits?
		push_token(stack, new);
		it->cur++;
		return (true);
	}
	return (false);
}

bool	tokenize_output(t_iterators *it, t_token_stack *stack)
{
	if (it->input[it->cur] == '>')
	{
		if (it->input[it->cur + 1] && it->input[it->cur + 1] == '>')
		{
			push_token(stack, create_token(DGREAT, gc_strdup(">>")));
			it->cur += 2;
		}
		else
		{
			push_token(stack, create_token(RED_TO, gc_strdup(">")));
			it->cur++;
		}
		return (true);
	}
	return (false);
}

bool	tokenize_input(t_iterators *it, t_token_stack *stack)
{
	if (it->input[it->cur] == '<')
	{
		if (it->cur + 1 < it->len && it->input[it->cur + 1] == '<')
		{
			push_token(stack, create_token(DLESS, gc_strdup("<<")));
			it->cur += 2;
		}
		else
		{
			push_token(stack, create_token(RED_FO, gc_strdup("<")));
			it -> cur ++;
		}
		return (true);
	}
	return (false);
}
