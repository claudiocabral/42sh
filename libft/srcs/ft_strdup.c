/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:53:12 by ccabral           #+#    #+#             */
/*   Updated: 2017/12/08 13:23:25 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <libft.h>

char	*ft_strdup(const char *src)
{
	char		*dup;
	size_t		size;

	size = ft_strlen(src);
	if ((dup = (char *)malloc(sizeof(char) * (size + 1))) == 0)
		return (0);
	ft_memcpy(dup, src, size + 1);
	return (dup);
}
