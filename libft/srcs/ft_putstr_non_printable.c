/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/06 16:06:33 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_hex(char c)
{
	char	*hex;

	hex = "0123456789ABCDEF";
	if (c >= 16)
		ft_putchar(hex[c / 16]);
	else
		ft_putchar('0');
	ft_putchar(hex[c % 16]);
}

void		ft_putstr_non_printable(const char *str)
{
	while (*str)
	{
		if (*str >= ' ' && *str != 127)
			ft_putchar(*str);
		else if (*str < 0)
		{
			ft_putchar(0);
			ft_putchar(0);
		}
		else
		{
			ft_putchar('\\');
			ft_print_hex(*str);
		}
		++str;
	}
}
