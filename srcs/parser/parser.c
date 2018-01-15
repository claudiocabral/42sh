/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 16:39:06 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <stdlib.h>
#include <array.h>
#include <tree.h>
#include <token.h>
#include <parser.h>
#include <ft_printf.h>

t_tree		*and_or(t_tree *tree, t_array *tokens, t_token **current)
{
	return (pipeline(tree, tokens, current));
}

t_tree		*list(t_tree *tree, t_array *tokens, t_token **current)
{
	t_token token;
	t_tree	*child;

	token = emit_token(LIST, 0, 0, 0);
	tree = tree_create_node(&token, sizeof(t_token));
	while (*current != tokens->end)
	{
		child = and_or(0, tokens, current);
		if (!child)
			break ;
		tree = tree_add_child(tree, child);
	}
	return (tree);
}

t_tree		*complete_command(t_tree *tree, t_array *tokens,
		t_token **current)
{
	tree = list(tree, tokens, current);
	return (tree);
}

t_tree		*parse(t_array *tokens)
{
	t_token	*current;
	t_tree	*tree;

	if (!tokens || tokens->begin == tokens->end)
	{
		array_free(tokens, &noop);
		return (0);
	}
	tree = 0;
	current = (t_token *)(tokens->begin);
	while (current != tokens->end)
	{
		tree = tree_add_child(tree, complete_command(0, tokens, &current));
		if (!tree)
			break ;
	}
	array_free(tokens, &noop);
	if (!tree)
		ft_dprintf(2, "parse error\n");
	return (tree);
}
