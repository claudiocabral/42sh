/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/08 13:18:56 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/08 15:40:50 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>

char	*ft_strndup(const char *src, size_t n)
{
	char		*dup;
	size_t		size;

	size = ft_strlen(src);
	size  = size > n ? n : size;
	ZERO_IF_FAIL(dup = (char *)malloc(sizeof(char) * (size + 1)));
	ft_memcpy(dup, src, size);
	dup[size] = 0;
	return (dup);
}
