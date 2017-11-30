/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_insert_data.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 13:44:06 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/27 11:55:00 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_btree.h"

t_btree	*btree_insert_data(t_btree **root,
		void *item, int (*cmpf)())
{
	t_btree	*ptr;

	ptr = 0;
	if (*root)
	{
		if (cmpf((*root)->item, item) > 0)
			ptr = btree_insert_data(&((*root)->left), item, cmpf);
		else
			ptr = btree_insert_data(&((*root)->right), item, cmpf);
	}
	else
	{
		ptr = btree_create_node(item);
		*root = ptr;
	}
	return(ptr);
}
