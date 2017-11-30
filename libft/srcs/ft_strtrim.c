/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 16:33:18 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:43:54 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_white(char const c)
{
	if (c == ' ' || c == ',' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;

	if (s == 0)
		return (NULL);
	start = 0;
	while (s[start] && ft_is_white(s[start]))
		++start;
	end = ft_strlen(s);
	if (end <= start)
		return ((char *)ft_memalloc(1));
	--end;
	while (ft_is_white(s[end]) && end != start)
		--end;
	return (ft_strsub(s, start, end - start + 1));
}
