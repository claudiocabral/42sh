/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 15:51:52 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 17:35:17 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (content == 0)
		content_size = 0;
	if (!(list = (t_list *)malloc(sizeof(t_list) + content_size)))
		return (0);
	list->next = NULL;
	list->content_size = content_size;
	if (content == 0)
	{
		list->content = 0;
		return (list);
	}
	list->content = list + sizeof(t_list);
	ft_memcpy(list->content, content, content_size);
	return (list);
}
