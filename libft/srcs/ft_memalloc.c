/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:06:31 by ccabral           #+#    #+#             */
/*   Updated: 2017/08/24 15:13:01 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	size_t	i;
	void	*data;

	if ((data = malloc(sizeof(char) * size)) == 0)
		return (NULL);
	i = 0;
	while (i < size)
		((char *)data)[i++] = 0;
	return (data);
}
