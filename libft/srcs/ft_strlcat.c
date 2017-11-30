/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:31:27 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 19:01:25 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static inline size_t	ft_min(size_t a, size_t b)
{
	return ((a < b) ? a : b);
}

unsigned int			ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t dest_len;
	size_t src_len;

	src_len = ft_strlen(src);
	dest_len = ft_min(ft_strlen(dest), size);
	if (src_len < size - dest_len)
		ft_strncat(dest, src, src_len + 1);
	else if (size > dest_len)
	{
		ft_strncat(dest, src, size - dest_len - 1);
		dest[size - 1] = '\0';
	}
	return (dest_len + src_len);
}
