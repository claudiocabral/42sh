/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   good_alias_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <ccabral@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/10 14:12:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/12 03:38:00 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

int			good_alias_name(char *tmp)
{
	int		i;

	i = 0;
	while (tmp[i])
	{
		ft_printf("c->%c\n", tmp[i]);
		if (tmp[i] == ' ' || tmp[i] == '\t')
			return (-1);
		++i;
	}
	return (1);
}
