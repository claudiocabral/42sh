/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:06:45 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 14:08:27 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

t_list		*ft_xlstnew(const void *cnt,
				size_t cnt_size)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->content = (void*)cnt;
	new->content_size = cnt_size;
	return (new);
}
