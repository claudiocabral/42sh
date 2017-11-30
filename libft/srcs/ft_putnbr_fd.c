/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 17:26:34 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int nb, int fd)
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
		ft_putchar_fd('-', fd);
		long_nb = -long_nb;
	}
	while (nmb_digits--)
	{
		ft_putchar_fd(long_nb / digits + '0', fd);
		long_nb %= digits;
		digits /= 10;
	}
}
