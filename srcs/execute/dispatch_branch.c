/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_branch.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/10 22:40:08 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/10 22:44:49 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <tree.h>
#include <token.h>
#include <execute.h>

int	branch_equals(t_tree *tree, t_tag type)
{
	return (((t_token *)tree->element)->type == type);
}

int	dispatch_branch(t_tree *tree)
{
	if (branch_equals(tree, PIPE))
		return (execute_pipe(tree));
	else
		return (execute_commands(tree));
}
