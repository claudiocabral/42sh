/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   offsetcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:08:08 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 14:08:25 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int			offsetcmp(const char *s1, const char *s2,
								char *tmp1, char *tmp2)
{
	tmp1 = (char*)s1;
	tmp2 = (char*)s2;
	while (*s1 && *s2 !ft_isalnum(*s1) && !ft_isalnum(*s2))
	{
		s1++;
		s2++;
	}
	if (*s1 && *s2)
	{
		while (ft_tolower((*s1)) == ft_tolower((*s2)) && *s1 && *s2)
		{
			s1++;
			s2++;
		}
		return (ft_tolower(*s1) - ft_tolower(*s2));
	}
	while (!ft_isalnum(*tmp1)
		&& !ft_isalnum(*tmp2)
		&& *tmp1 == *tmp2)
	{
		tmp1++;
		tmp2++;
	}
	return (*tmp1 - *tmp2);
}
