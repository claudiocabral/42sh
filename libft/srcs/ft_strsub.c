/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:49:05 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:43:53 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char	*cpy;
	size_t	i;
	size_t	j;

	if (s == 0)
		return (NULL);
	if ((cpy = (char *)malloc(sizeof(char) * (len + 1))) == 0)
		return (NULL);
	i = start;
	j = 0;
	while (i < start + len)
	{
		cpy[j] = s[i];
		++j;
		++i;
	}
	cpy[j] = 0;
	return (cpy);
}
