/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:48:09 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 19:11:08 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_strlcpy(char *dest, const char *src, unsigned int size)
{
	unsigned int	count;

	if (size == 0)
		return (ft_strlen(src));
	count = 0;
	while (size > 1 && *src)
	{
		*dest = *src;
		++dest;
		++src;
		--size;
		++count;
	}
	*dest = '\0';
	while (*dest || *src)
	{
		if (*src)
		{
			++src;
			++count;
		}
	}
	return (count);
}
