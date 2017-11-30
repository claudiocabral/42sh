/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 17:03:48 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 13:26:20 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

static void	fill_characters(char *str, int nb)
{
	int		nb_digits;
	int		digits;
	long	long_nb;

	nb_digits = 1;
	long_nb = nb;
	digits = 1;
	while (nb > 9 || nb < -9)
	{
		nb_digits++;
		digits *= 10;
		nb /= 10;
	}
	if (long_nb < 0)
	{
		*str++ = '-';
		long_nb = -long_nb;
	}
	while (nb_digits--)
	{
		*str++ = long_nb / digits + '0';
		long_nb %= digits;
		digits /= 10;
	}
	*str = 0;
}

char		*ft_itoa(int nb)
{
	char	*str;
	size_t	size;
	int		tmp_nb;

	size = 1;
	tmp_nb = nb;
	while (nb > 9 || nb < -9)
	{
		++size;
		nb /= 10;
	}
	if (nb < 0)
		++size;
	if ((str = (char *)malloc(sizeof(char) * (size + 1))) == 0)
		return (NULL);
	fill_characters(str, tmp_nb);
	return (str);
}
