/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/02 14:32:38 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:30 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr(int nb)
{
	long	digits;
	long	nmb_digits;
	long	long_nb;

	digits = 1;
	nmb_digits = 1;
	long_nb = nb;
	while (nb > 9 || nb < -9)
	{
		nmb_digits++;
		digits *= 10;
		nb /= 10;
	}
	if (long_nb < 0)
	{
		ft_putchar('-');
		long_nb = -long_nb;
	}
	while (nmb_digits--)
	{
		ft_putchar(long_nb / digits + '0');
		long_nb %= digits;
		digits /= 10;
	}
}
