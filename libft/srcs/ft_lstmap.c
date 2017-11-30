/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 15:51:50 by claudioca         #+#    #+#             */
/*   Updated: 2017/11/06 17:42:27 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	**new;
	t_list	**head;
	t_list	*dummy;

	dummy = 0;
	head = &dummy;
	new = head;
	while (lst)
	{
		*head = f(lst);
		lst = lst->next;
		head = &((*head)->next);
	}
	return (*new);
}
