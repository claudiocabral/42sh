/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:45:14 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <stdlib.h>
#include <array.h>
#include <tree.h>
#include <token.h>
#include <ast_node.h>

t_tree		*command_name(t_token **current)
{
	t_ast_node	node;
	t_tree		*tree;

	node = ast_node_create(COMMAND_NAME, *current);
	ZERO_IF_FAIL(tree = tree_create_node((void *)&node, sizeof(t_ast_node)));
	++(*current);
	return (tree);
}

t_tree		*simple_command(t_array *tokens, t_token **current)
{
	t_ast_node	node;
	t_tree		*tree;

	(void)tokens;
	node = ast_node_create(SIMPLE_COMMAND, 0);
	ZERO_IF_FAIL(tree = tree_create_node(&node, sizeof(t_ast_node)));
	tree_add_child(tree, command_name(current));
	return (tree);
}

t_tree		*command(t_tree *tree, t_array *tokens, t_token **current)
{
	(void)tree;
	return (simple_command(tokens, current));
}

t_tree		*pipeline_sequence(t_tree *tree, t_array *tokens, t_token **current)
{
	return (command(tree, tokens, current));
}

t_tree		*pipeline(t_tree *tree, t_array *tokens, t_token **current)
{
	return (pipeline_sequence(tree, tokens, current));
}

t_tree		*and_or(t_tree *tree, t_array *tokens, t_token **current)
{
	return (pipeline(tree, tokens, current));
}

t_tree		*list(t_tree *tree, t_array *tokens, t_token **current)
{
	return (and_or(tree, tokens, current));
}

t_tree	*complete_command(t_tree *tree, t_array *tokens,
		t_token **current)
{
	//t_tree	*tree;

	//if (!token_separator(peek(tokens, current, 1)))
	return (list(tree, tokens, current));
}

t_tree	*parse(t_array *tokens)
{
	t_token	*current;
	t_tree	*tree;

	current = (t_token *)tokens->begin;
	tree = complete_command(0, tokens, &current);
	array_free(tokens, &noop);
	ZERO_IF_FAIL(tree);
	return (tree);
}
