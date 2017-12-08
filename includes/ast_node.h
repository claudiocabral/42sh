/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_node.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:13:21 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:40:57 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_NODE_H
# define AST_NODE_H

# include <token.h>

typedef enum	e_ast_type
{
	SIMPLE_COMMAND,
	COMMAND_NAME
}				t_ast_type;

typedef struct	s_ast_node
{
	t_ast_type	type;
	t_token		token;
}				t_ast_node;

t_ast_node	ast_node_create(t_ast_type type, t_token *token);

#endif
