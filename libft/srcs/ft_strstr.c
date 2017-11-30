/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 09:20:00 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:43:52 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char	*head;
	const char	*tmp;

	if (!*little)
		return ((char *)big);
	tmp = little;
	while (*big)
	{
		head = big;
		while ((*big == *little) && *little)
		{
			++big;
			++little;
		}
		if (!*little)
			return ((char *)head);
		little = tmp;
		big = head + 1;
	}
	return (0);
}
