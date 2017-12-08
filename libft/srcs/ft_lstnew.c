/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 15:51:52 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 17:18:12 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (!(list = (t_list *)malloc(sizeof(t_list))))
		return (0);
	list->next = NULL;
	if (content == 0)
	{
		list->content = 0;
		list->content_size = 0;
		return (list);
	}
	if (!(list->content = malloc(content_size)))
		return (NULL);
	ft_memcpy(list->content, content, content_size);
	list->content_size = content_size;
	return (list);
}

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*list;

	if (content == 0)
		element_size = 0;
	if (!(list = (t_list *)malloc(sizeof(t_list + element_size))))
		return (0);
	list->next = NULL;
	list->content = list + sizeof(t_list);
	ft_memcpy(list->content, content, content_size);
	list->content_size = content_size;
	return (list);
}
