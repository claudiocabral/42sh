/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:40:58 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:43:35 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	unsigned int	len;
	char			*map;
	char			*head;

	if (s == 0)
		return (NULL);
	len = ft_strlen(s) + 1;
	if ((map = (char *)malloc(sizeof(char) * len)) == 0)
		return (NULL);
	head = map;
	while (*s)
		*map++ = f(*s++);
	*map = 0;
	return (head);
}
