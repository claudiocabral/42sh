/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:11:57 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/21 13:20:12 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	ft_apply_to_level(t_btree *node, int level, int val,
					void (*applyf)(void *, int, int))
{
	static int	first = 1;

	if (!node)
		return ;
	else if (level == 0)
	{
		applyf(node->item, val, first);
		first = 0;
	}
	else
	{
		ft_apply_to_level(node->left, level - 1, val + 1, applyf);
		ft_apply_to_level(node->right, level - 1, val + 1, applyf);
	}
	if (val == 0)
		first = 1;
}

void	btree_apply_by_level(t_btree *root,
				void (*applyf)(void *, int, int))
{
	int			i;
	int			size;

	if (!root)
		return ;
	i = 0;
	size = btree_level_count(root);
	while (i < size)
	{
		ft_apply_to_level(root, i, 0, applyf);
		++i;
	}
}
