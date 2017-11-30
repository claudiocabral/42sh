/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:44:23 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/14 16:15:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "print.h"
#include "utils.h"

void	generic_print(t_modifiers *modifiers, t_getter get_value,
												t_generate_string generator,
												t_print print)
{
	char		*str;

	if (!(str = generator(get_value(modifiers), modifiers)))
		exit(1);
	print(str, modifiers);
	free(str);
}

void	print_with_padding(char const *str, t_modifiers *modifiers, int size)
{
	int	padding;
	int	precision;

	precision = ftprintf_max(modifiers->precision, size);
	padding = modifiers->field_width - size;
	if (!(modifiers->flags & MINUS))
		print_padding(padding, modifiers->flags & ZERO);
	write_and_count(str, size);
	if ((modifiers->flags & MINUS))
		print_padding(padding, 0);
}

void	print_padding(int size, int use_zero)
{
	char	c;

	c = ' ';
	if (use_zero)
		c = '0';
	while (size-- > 0)
		write_and_count(&c, 1);
}

char	get_number_sign(long value, t_modifiers *modifiers)
{
	if (value < 0)
		return ('-');
	else if (modifiers->flags & PLUS)
		return ('+');
	else if (modifiers->flags & SPACE)
		return (' ');
	return (0);
}
