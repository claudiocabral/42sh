/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 19:02:35 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/09 13:53:33 by ccabral          ###   ########.fr       */
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
	tree_add_child(tree, command_name(current));
	while(*current != tokens->end && !match(current, SEMICOLON))
	{
		tree_add_child(tree, command_name(current));
	}
	return (tree);
}

t_tree		*command(t_tree *tree, t_array *tokens, t_token **current)
{
	t_token		token;
	t_tree	*commands;

	(void)tree;
	token = emit_token(SIMPLE_COMMAND, 0, 0, 0);
	commands = tree_create_node(&tokens, sizeof(t_token));
	while(*current != tokens->end)
	{
		if (match(current, SEMICOLON))
			continue ;
		tree_add_child(commands, simple_command(tokens, current));
	}
	return (commands);
}

t_tree		*pipeline_sequence(t_tree *tree, t_array *tokens, t_token **current)
{
	t_tree	*pipe;
	int		ret;

	ret = 0;
	while (1)
	{
		tree = command(tree, tokens, current);
		if (*current == tokens->end)
			break ;
		if (match(current, PIPE))
		{
			if (!(pipe = tree_create_node(*(current - 1), sizeof(t_token))))
			{
				ret = -1;
				break ;
			}
		}
	}
	if (ret == -1)
	{
		tree_free(tree, (t_freef)free_wrapper);
		return (0);
	}
	return (tree);
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
	while (*current != tokens->end)
	{
		tree = and_or(tree, tokens, current);
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

	if (!tokens)
		return (0);
	tree = 0;
	current = (t_token *)(tokens->begin);
	while (current != tokens->end)
	{
		if (match(&current, SEMICOLON))
			continue ;
		tree = tree_add_child(tree, complete_command(0, tokens, &current));
	}
	array_free(tokens, &noop);
	ZERO_IF_FAIL(tree);
	return (tree);
}
