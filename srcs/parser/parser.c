/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 09:49:57 by ccabral          ###   ########.fr       */
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
	while (*current != tokens->end)
	{
		if (!(tree = and_or(tree, tokens, current)))
			break ;
		//separator_op(tree, tokens, current);
	}
	return (tree);
}

t_tree	*complete_command(t_tree *tree, t_array *tokens,
		t_token **current)
{
	tree = list(tree, tokens, current);
	//separator(tree, tokens, current);
	return (tree);
}


t_tree	*parse(t_array *tokens)
{
	t_token	*current;
	t_tree	*tree;

	if (!tokens || tokens->begin == tokens->end)
		return (0);
	tree = 0;
	current = (t_token *)(tokens->begin);
	while (current != tokens->end)
	{
		if (match(&current, SEMICOLON, SENTINEL))
			continue ;
		tree = tree_add_child(tree, complete_command(0, tokens, &current));
		if (!tree)
			break ;
	}
	array_free(tokens, &noop);
	if (!tree)
		ft_dprintf(2, "parse error\n");
	return (tree);
}
