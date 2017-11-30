/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 14:40:24 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 13:37:14 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	const char	*head;

	head = s;
	while (*s)
		++s;
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (s-- == head)
			break ;
	}
	return (NULL);
}
