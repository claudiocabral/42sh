/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:43:45 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 18:12:55 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	len;
	unsigned int	i;
	char			*map;

	if (s == 0)
		return (NULL);
	len = ft_strlen(s) + 1;
	if ((map = (char *)malloc(sizeof(char) * len)) == 0)
		return (NULL);
	i = 0;
	while (s[i++])
		map[i - 1] = f(i - 1, s[i - 1]);
	map[i - 1] = 0;
	return (map);
}
