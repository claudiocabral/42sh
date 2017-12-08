/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 18:50:24 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:33:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <shellma.h>
#include <execute.h>
#include <signal_handlers.h>
#include <ft_printf.h>
#include <ast_node.h>

char	**environ;

int		is_command_argument(t_ast_node *node)
{
	(void)node;
	return (0);
}

char	*ast_node_get_value(t_ast_node *node)
{
	return (ft_strndup(node->token.begin, node->token.size));
}

void	execute_simple_command(t_tree *tree)
{
	t_array		*args;
	t_ast_node	*child;

	args = array_create(sizeof(char *), 16);
	child =  (t_ast_node *)tree->children->begin;
	array_push_back(args, ast_node_get_value(child));
	++child;
	while (child != tree->children->end && is_command_argument(child))
	{
		array_push_back(args, ast_node_get_value(child));
	}
	execve(((char const **)args->begin)[0], (char **)args->begin, environ);
}

void	execute(t_tree *tree)
{
	execute_simple_command(tree);
}
