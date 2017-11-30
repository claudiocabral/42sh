/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 14:37:39 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:59 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strchr(char const *s, int c)
{
	while (1)
	{
		if (*s == (char)c)
			return ((char *)s);
		if (!*s++)
			break ;
	}
	return (NULL);
}
