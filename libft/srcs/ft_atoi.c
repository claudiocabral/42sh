/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/03 11:35:52 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 18:22:01 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		signal;
	long	num;

	num = 0;
	signal = 1;
	while (*str <= 32 && *str > 0)
	{
		if (*str == '\e')
			return (0);
		++str;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signal *= -1;
		++str;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		num *= 10;
		num += (*str - 48);
		++str;
	}
	num *= signal;
	return (num);
}
