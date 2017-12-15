/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_power_of_two.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 11:55:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 15:06:05 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t			ft_next_power_of_two(size_t value)
{
	size_t	i;

	i = 0;
	while (value)
	{
		value >>= 1;
		++i;
	}
	return (1 << i);
}
