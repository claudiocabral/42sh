/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 11:25:49 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 16:20:54 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_H
# define TREE_H

# include <array.h>

typedef struct	s_tree
{
	void			*element;
	size_t			element_size;
	struct s_tree	*parent;
	t_array			*children;
}				t_tree;

t_tree			*tree_create_node(void *element, size_t element_size);
t_tree			*tree_add_child(t_tree *parent, t_tree *child);

#endif
