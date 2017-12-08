/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:42:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:40:14 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ast_node.h>

t_ast_node	ast_node_create(t_ast_type type, t_token *token)
{
	t_ast_node	node;

	node.type = type;
	if (token)
	{
		node.token.type = token->type;
		node.token.begin = token->begin;
		node.token.size = token->size;
	}
	else
		node.token.type = TOKEN_NIL;
	return (node);
}
