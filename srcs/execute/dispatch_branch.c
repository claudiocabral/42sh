/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_branch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 22:40:08 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 16:34:26 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tree.h>
#include <token.h>
#include <execute.h>

int	branch_equals(t_tree *tree, t_tag type)
{
	return (((t_token *)tree->element)->type == type);
}

int	execute_list(t_tree *tree)
{
	t_tree	**it;
	int		ret;

	it = (t_tree **)tree->children->begin;
	while (it != tree->children->end)
	{
		ret = dispatch_branch(*it);
		++it;
	}
	return (ret);
}

int	dispatch_branch(t_tree *tree)
{
	if (branch_equals(tree, LIST))
		return (execute_list(tree));
	else if (branch_equals(tree, PIPE))
		return (execute_pipe(tree));
	else
		return (execute_commands(tree));
}
