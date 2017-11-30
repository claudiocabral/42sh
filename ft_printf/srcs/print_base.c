/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 15:34:30 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/13 11:16:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <print.h>

static unsigned long long	g_count = 0;

unsigned long long			write_and_count(char const *str, size_t size)
{
	g_count += size;
	write(1, str, size);
	return (g_count);
}

void						increase_count(unsigned int size)
{
	g_count += size;
}

inline unsigned long long	get_character_count(void)
{
	return (g_count);
}

inline void					reset_character_count(void)
{
	g_count = 0;
}

char const					*print_formated(char const *format,
												t_modifiers *modifiers)
{
	t_function	f;

	f = get_printer(modifiers->type);
	format = f(format, modifiers);
	return (format);
}
