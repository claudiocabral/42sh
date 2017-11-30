/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpush_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:38:53 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:27 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstpush_back(t_list **lst, void const *content, size_t content_size)
{
	if (!lst)
		return ;
	while (*lst)
		lst = &((*lst)->next);
	*lst = ft_lstnew(content, content_size);
}
