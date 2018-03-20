/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 16:12:22 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/20 19:36:00 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parser.h>
#include <token.h>
#include <array.h>

static t_tree	*add_redirect_arguments(t_tree *tree, t_tree *number,
										t_array *tokens, t_token **current)
{
	ZERO_IF_FAIL(tree = tree_add_child(tree, tree_create_node(*(current) - 1,
													sizeof(t_token))));
	if (tree && number)
		tree_add_child(tree, number);
	if (*current != tokens->end && match(current, TOKEN, SENTINEL))
		tree_add_child(tree, tree_create_node(*current - 1, sizeof(t_token)));
	else
	{
		tree_free(tree, (t_freef) & noop);
		return (0);
	}
	return (tree);
}

t_tree			*io_redirect(t_array *tokens, t_token **current)
{
	t_tree	*number;
	t_tree	*redirection;

	number = 0;
	if (match(current, IO_NUMBER, SENTINEL))
		number = tree_create_node(*current - 1, sizeof(t_token));
	if (!match(current, LESS, DLESS, LESSAND,
				GREATER, DGREATER, GREATERAND, SENTINEL)
			|| *current == tokens->end
			|| !(redirection = tree_create_node(*current - 1,
												sizeof(t_token))))
	{
		tree_free(number, (t_freef) & noop);
		return (0);
	}
	return (add_redirect_arguments(0, number, tokens, current));
}
