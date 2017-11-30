/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 12:51:50 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_base_valid(const char *base)
{
	const char	*iter;

	iter = base;
	if (!*base)
		return (0);
	while (*iter)
	{
		if (!(*iter) || *iter == '+' || *iter == '-'
				|| *iter < ' ' || *iter == 127)
			return (0);
		base = iter + 1;
		while (*base)
		{
			if (*base == *iter)
				return (0);
			++base;
		}
		++iter;
	}
	return (1);
}

static long	ft_get_base_size(const char *base)
{
	int	size;

	size = 0;
	while (*base)
	{
		++base;
		++size;
	}
	return (size);
}

static void	ft_show_number(long nbr, const char *base,
							long *power_x, int nbr_size)
{
	long	digit;

	if (nbr < 0)
	{
		ft_putchar('-');
		nbr = -nbr;
	}
	while (nbr_size--)
	{
		digit = nbr / power_x[nbr_size];
		ft_putchar(base[digit]);
		nbr %= power_x[nbr_size];
	}
}

void		ft_putnbr_base(int nbr, const char *base)
{
	int		last_digit;
	int		i;
	long	power_x[21];

	if (!ft_is_base_valid(base))
		return ;
	power_x[0] = 1;
	power_x[1] = ft_get_base_size(base);
	i = 1;
	last_digit = nbr;
	while (last_digit >= power_x[1] || last_digit <= power_x[1] * -1)
	{
		++i;
		power_x[i] = power_x[i - 1] * power_x[1];
		last_digit /= power_x[1];
	}
	ft_show_number(nbr, base, power_x, i);
}
