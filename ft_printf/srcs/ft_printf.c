/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 13:23:51 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/26 14:45:20 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "modifiers.h"
#include "print.h"
#include "checks.h"
#include "percent.h"
#include "string.h"
#include "getters.h"

static char const	*parse_and_process(char const *format,
					t_modifiers *modifiers)
{
	t_function	f;

	while (*format)
	{
		f = get_function(*format);
		format = f(format, modifiers);
		if (f == &conversion)
			break ;
	}
	format = print_formated(format, modifiers);
	reset_modifiers(modifiers);
	return (format);
}

static int			print_loop(char const *format, t_modifiers *modifiers)
{
	char const			*start;
	size_t				size;

	start = format;
	while (*format)
	{
		if (*format == '%')
		{
			size = format - start;
			write_and_count(start, size);
			format = parse_and_process(format + 1, modifiers);
			if (format == 0)
				return (0);
			start = format;
		}
		else
			++format;
	}
	write_and_count(start, format - start);
	return (1);
}

int					ft_printf(char const *format, ...)
{
	va_list				args;
	t_modifiers			modifiers;
	unsigned long long	ret;

	ret = 0;
	va_start(args, format);
	init_modifiers(&modifiers, &args);
	va_end(args);
	if (!print_loop(format, &modifiers))
		return (-1);
	clean_modifiers(&modifiers);
	ret = get_character_count();
	reset_character_count();
	return (ret);
}
