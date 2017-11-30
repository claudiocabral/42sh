/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_create_node.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 13:24:42 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/21 16:45:32 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_btree.h"

t_btree	*btree_create_node(void *item)
{
	t_btree	*node;

	if (!(node = malloc(sizeof(t_btree))))
		return (0);
	node->item = item;
	node->left = 0;
	node->right = 0;
	return (node);
}

void	btree_free(t_btree **root, void (*free_func)(void *))
{
	if (*root)
	{
		btree_free(&((*root)->left), free_func);
		btree_free(&((*root)->right), free_func);
		free_func((*root)->item);
		free(*root);
		*root = 0;
	}
}
