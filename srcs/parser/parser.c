/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/19 14:59:11 by ccabral          ###   ########.fr       */
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
	t_tree	*branch;

	branch = 0;
	while (1)
	{
		if (peek(current, AND_IF, OR_IF, SENTINEL))
		{
			branch = tree_add_child(branch,
					tree_create_node(*current++, sizeof(t_token)));
		}
		else if (*current != tokens->end)
			branch = pipeline(branch, tokens, current);
		else
			break ;
	}
	return (tree_add_child(tree, branch));
}

t_tree		*list(t_tree *tree, t_array *tokens, t_token **current)
{
	t_token token;
	t_tree	*child;

	token = emit_token(LIST, 0, 0, 0);
	ZERO_IF_FAIL(tree = tree_create_node(&token, sizeof(t_token)));
	while (*current != tokens->end)
	{
		if (match(current, SEMICOLON, SENTINEL))
			continue ;
		child = and_or(0, tokens, current);
		if (!child)
		{
			tree_free(tree, (t_freef) & noop);
			return (0);
		}
		tree = tree_add_child(tree, child);
	}
	if (tree->children->begin == tree->children->end)
	{
		tree_free(tree, (t_freef) & noop);
		return (0);
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
	t_tree	*child;

	if (!tokens || tokens->begin == tokens->end)
	{
		array_free(tokens, &noop);
		return (0);
	}
	tree = 0;
	current = (t_token *)(tokens->begin);
	while (current != tokens->end)
	{
		if (!(child = complete_command(0, tokens, &current)))
			break ;
		tree = tree_add_child(tree, child);
		if (!tree)
			break ;
	}
	array_free(tokens, &noop);
	if (!tree)
		ft_dprintf(2, "parse error\n");
	return (tree);
}
