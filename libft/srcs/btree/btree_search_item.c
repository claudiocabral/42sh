/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:04:21 by ccabral           #+#    #+#             */
/*   Updated: 2017/08/18 12:45:09 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
		int (*cmpf)(void*, void*))
{
	int	cmp;

	if (!root)
		return (0);
	cmp = cmpf(root->item, data_ref);
	if (cmp == 0)
		return (root->item);
	else if (cmp > 0)
		return (btree_search_item(root->left, data_ref, cmpf));
	else if (cmp < 0)
		return (btree_search_item(root->right, data_ref, cmpf));
	return (0);
}
