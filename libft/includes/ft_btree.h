/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 11:45:16 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/12 11:24:50 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BTREE_H
# define FT_BTREE_H

# include <libft.h>

typedef struct		s_btree
{
	struct s_btree	*left;
	struct s_btree	*right;
	void			*item;
}					t_btree;

t_btree				*btree_create_node(void *item);
void				btree_free(t_btree **root, void (*free_func)(void *));
void				btree_apply_prefix(t_btree *root, void *args,
															t_applyf applyf);
void				btree_apply_infix(t_btree *root, void *args,
															t_applyf applyf);
void				btree_apply_suffix(t_btree *root, void *args,
															t_applyf applyf);
t_btree				*btree_insert_data(t_btree **root, void *item, t_cmpf cmpf);
void				*btree_search_item(t_btree *root, void *data_ref,
																t_cmpf cmpf);
int					btree_level_count(t_btree *root);
void				btree_apply_by_level(t_btree *root,
									void (*applyf)(void *, int, int));

#endif
