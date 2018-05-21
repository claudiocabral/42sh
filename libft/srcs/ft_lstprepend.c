/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:07:28 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 14:08:26 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void		ft_lstprepend(t_list **addr,
					t_list *lst)
{
	t_list	*tmp;

	tmp = *addr;
	if (tmp != NULL)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lst;
	}
	else
		*addr = lst;
}
