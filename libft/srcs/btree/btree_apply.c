/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 13:17:44 by claudioca         #+#    #+#             */
/*   Updated: 2017/11/30 13:13:34 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	btree_apply_infix(t_btree *root, void *params, t_applyf applyf)
{
	if (root)
	{
		btree_apply_infix(root->left, params, applyf);
		applyf(root->item, params);
		btree_apply_infix(root->right, params, applyf);
	}
}

void	btree_apply_prefix(t_btree *root, void *params, t_applyf applyf)
{
	if (root)
	{
		applyf(root->item, params);
		btree_apply_prefix(root->left, params, applyf);
		btree_apply_prefix(root->right, params, applyf);
	}
}

void	btree_apply_suffix(t_btree *root, void *params, t_applyf applyf)
{
	if (root)
	{
		btree_apply_suffix(root->right, params, applyf);
		applyf(root->item, params);
		btree_apply_suffix(root->left, params, applyf);
	}
}
