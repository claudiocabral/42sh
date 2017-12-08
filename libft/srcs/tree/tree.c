/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:30:59 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 17:24:48 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <tree.h>

t_tree			*tree_create_node(void *element, size_t element_size)
{
	t_tree	*tree;

	ZERO_IF_FAIL(tree = (t_tree *)malloc(sizeof(t_tree)
				+ sizeof(t_array *)
				+ element_size));
	tree->children = tree + sizeof(t_tree);
	tree->element = tree->children + sizeof(t_array *);
	tree->parent = 0;
	tree->element_size = element_size;
	ft_memcpy(tree->element, element, element_size);
	return (tree);
}

t_tree			*tree_add_child(t_tree *parent, t_tree *child)
{
	ZERO_IF_FAIL(array_push_back(parent->children, child));
	child->parent = parent;
	return (parent);
}
