/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_search_item.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 14:04:21 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/05 10:56:24 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

void	*btree_search_item(t_btree *root, void *data_ref,
		t_cmpf cmpf)
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
