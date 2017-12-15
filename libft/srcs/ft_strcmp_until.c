/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_until.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 17:32:23 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 17:43:58 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int	ft_strcmp_until(char const *s1, char const *s2, char c)
{
	while (*s1 == *s2)
	{
		++s1;
		++s2;
		if (*s2 == c)
			return (0);
		if (*s1 == '\0')
			break ;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
