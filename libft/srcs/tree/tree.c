/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 15:30:59 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/18 16:18:39 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <tree.h>

t_tree			*tree_create_node(void *element, size_t element_size)
{
	t_tree	*tree;

	ZERO_IF_FAIL(element == 0 || element_size == 0
			|| (tree = (t_tree *)malloc(sizeof(t_tree) + element_size)));
	tree->element = (t_array *)((char *)tree + sizeof(t_tree));
	if (!(tree->children = array_create(sizeof(t_tree *), 8)))
	{
		free(tree);
		return (0);
	}
	tree->children->end = tree->children->begin;
	tree->children->element_size = sizeof(t_tree *);
	tree->children->capacity = 8 * tree->children->element_size;
	tree->parent = 0;
	tree->element_size = element_size;
	ft_memcpy(tree->element, element, element_size);
	return (tree);
}

t_tree			*tree_add_child(t_tree *parent, t_tree *child)
{
	if (parent)
	{
		child->parent = parent;
		ZERO_IF_FAIL(array_push_back(parent->children, &child));
		return (parent);
	}
	return (child);
}

void			tree_apply_infix(t_tree *node, void *args, t_applyf applyf)
{
	t_tree	**child;

	if (!node)
		return ;
	child = (t_tree **)node->children->begin;
	while (child != node->children->end)
	{
		tree_apply_infix(*child, args, applyf);
		++child;
	}
	applyf(node->element, args);
}
