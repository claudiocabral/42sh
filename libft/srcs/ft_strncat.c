/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:19:06 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:50:16 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncat(char *dest, const char *src, size_t nb)
{
	char	*head;

	if (nb == 0)
		return (dest);
	head = dest;
	while (*dest)
	{
		++dest;
	}
	while (*src && nb > 0)
	{
		*dest = *src;
		++dest;
		++src;
		--nb;
	}
	*dest = '\0';
	return (head);
}
