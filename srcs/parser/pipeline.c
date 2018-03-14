/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/14 18:24:22 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <stdlib.h>
#include <array.h>
#include <tree.h>
#include <token.h>
#include <parser.h>

t_tree		*command_name(t_token **current)
{
	t_tree		*tree;

	(*current)->type = NAME;
	ZERO_IF_FAIL(tree = tree_create_node(*current, sizeof(t_token)));
	++(*current);
	return (tree);
}

t_tree		*simple_command(t_array *tokens, t_token **current)
{
	t_token		token;
	t_tree		*tree;

	token = emit_token(SIMPLE_COMMAND, 0, 0, 0);
	ZERO_IF_FAIL(tree = tree_create_node(&token, sizeof(t_token)));
	while (*current != tokens->end)
	{
		if (match(current, SEMICOLON, PIPE, SENTINEL))
		{
			--(*current);
			return (tree);
		}
		else if (match(current, IO_NUMBER, LESS, DLESS, LESSAND, GREATERAND,
												GREATER, DGREATER, SENTINEL))
		{
			--(*current);
			tree_add_child(tree, io_redirect(tokens, current));
		}
		else
			tree_add_child(tree, command_name(current));
	}
	return (tree);
}

t_tree		*command(t_tree *tree, t_array *tokens, t_token **current)
{
	t_token		token;
	t_tree		*commands;

	if (!match(current, TOKEN, SENTINEL))
		return (0);
	else
		--(*current);
	token = emit_token(COMMANDS, 0, 0, 0);
	commands = tree_create_node(&token, sizeof(t_token));
	while (*current != tokens->end)
	{
		if (match(current, SEMICOLON, PIPE, SENTINEL))
		{
			--(*current);
			break ;
		}
		tree_add_child(commands, simple_command(tokens, current));
	}
	tree = tree_add_child(tree, commands);
	return (tree);
}

t_tree		*pipeline_sequence(t_tree *tree, t_array *tokens, t_token **current)
{
	t_tree	*child;

	child = 0;
	while (1)
	{
		if (match(current, SEMICOLON, SENTINEL))
			break ;
		if (!(child = command(0, tokens, current)))
		{
			tree_free(tree, (t_freef) & noop);
			return (0);
		}
		tree = tree_add_child(tree, child);
		if (*current == tokens->end)
			break ;
		if (match(current, PIPE, SENTINEL))
		{
			child = tree_create_node(*(current) - 1, sizeof(t_token));
			tree = tree_add_child(child, tree);
		}
	}
	return (tree);
}

t_tree		*pipeline(t_tree *tree, t_array *tokens, t_token **current)
{
	return (pipeline_sequence(tree, tokens, current));
}
