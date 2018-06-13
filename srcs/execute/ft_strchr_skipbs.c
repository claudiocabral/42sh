/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_skipbs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 11:06:41 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/13 11:06:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execute.h>

char	*ft_strchr_skipbs(char const *s, int c)
{
	while (1)
	{
		if (*s == '\\')
		{
			if (!*s++)
				break ;
		}
		else if (*s == (char)c)
			return ((char *)s);
		if (!*s++)
			break ;
	}
	return (NULL);
}
