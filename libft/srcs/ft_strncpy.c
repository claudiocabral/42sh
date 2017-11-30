/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/05 17:59:53 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 18:11:55 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	char			*head;

	if (len == 0)
		return (dest);
	head = dest;
	while (*src && len > 0)
	{
		*dest++ = *src++;
		--len;
	}
	while (len > 0)
	{
		*dest++ = '\0';
		--len;
	}
	return (head);
}
