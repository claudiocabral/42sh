/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 14:16:22 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 18:10:43 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include "libft.h"

inline static size_t	ft_min(size_t a, size_t b)
{
	return ((a < b) ? a : b);
}

void					*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*mem[64];
	size_t	size;
	size_t	i;

	i = 0;
	size = ft_min(64, len);
	while (1)
	{
		ft_memcpy(mem, src + i, size);
		ft_memcpy(dst + i, mem, size);
		if (len <= size + i)
			return (dst);
		i += size;
		size = ft_min(64, len - i);
	}
	return (dst);
}
