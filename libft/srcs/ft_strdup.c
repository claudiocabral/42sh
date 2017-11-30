/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 17:53:12 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 13:34:11 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *src)
{
	const char	*head;
	char		*dup;
	int			size;

	head = src;
	size = 1;
	while (*src)
	{
		++size;
		++src;
	}
	if ((dup = (char *)malloc(sizeof(char) * size)) == 0)
		return (NULL);
	src = head;
	head = dup;
	while (*src)
		*dup++ = *src++;
	*dup = '\0';
	return ((char *)head);
}
