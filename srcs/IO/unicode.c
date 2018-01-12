/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unicode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 15:44:17 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/12 15:46:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		is_middle_of_unicode(unsigned char c)
{
	return ((c & 0xc0) == 0x80);
}

int		cursor_is_middle_of_unicode(t_terminal *terminal)
{
	return (is_middle_of_unicode(terminal->line->buffer[terminal->cursor
						- terminal->prompt_size]));
}

int		get_letter_index(t_terminal *terminal)
{
	int	i;

	i = 0;
	if (terminal->line->buffer[terminal->cursor - terminal->prompt_size]
			& 0x80)
		++i;
	while (is_middle_of_unicode(
			terminal->line->buffer[terminal->cursor
								- terminal->prompt_size - i]))
		++i;
	return (i);
}
