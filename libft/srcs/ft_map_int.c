/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 09:25:54 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/07 09:26:12 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	*ft_map_int(int *tab, int length, int (*f)(int))
{
	int		*map;
	int		*head;

	map = malloc(sizeof(int) * length);
	head = map;
	while (length-- > 0)
		*map++ = (*f)(*tab++);
	return (head);
}
