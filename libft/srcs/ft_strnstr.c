/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 14:43:51 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:43:46 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	const char	*head;
	const char	*tmp;
	size_t		i;

	if (!*little)
		return ((char *)big);
	tmp = little;
	while (*big && len)
	{
		head = big;
		i = 0;
		while ((*big == *little) && *little && i < len)
		{
			++big;
			++little;
			++i;
		}
		if (!*little)
			return ((char *)head);
		little = tmp;
		big = head + 1;
		--len;
	}
	return (0);
}
