/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_copy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:47:05 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 14:10:13 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <slice.h>
#include <libft.h>
#include <io.h>

t_slice	copy_loop(t_terminal *terminal, char buffer[16])
{
	t_slice	clip;
	char	*begin;
	char	*end;
	int		tmp;

	tmp = terminal->cursor;
	begin = terminal->line->buffer + terminal->cursor;
	while ((clip.size = read(STDIN_FILENO, buffer, 15)) > 0)
	{
		buffer[clip.size] = 0;
		if (terminal_compare_string(ARROW_LEFT, buffer))
			terminal_standout(terminal, tmp, -1);
		else if (terminal_compare_string(ARROW_RIGHT, buffer))
			terminal_standout(terminal, tmp, 1);
		else if (*buffer == 25)
			break ;
	}
	end = terminal->line->buffer + terminal->cursor;
	if (begin < end)
		clip = slice_from_pointers(begin, end + 1);
	else
		clip = slice_from_pointers(end, begin + 1);
	restore_terminal_position(terminal, tmp);
	return (clip);
}

int		terminal_copy(t_terminal *terminal, int c)
{
	t_slice	clip;
	char	buffer[16];

	(void)c;
	terminal_command(STANDOUT, 0);
	terminal_rewrite(terminal);
	clip = copy_loop(terminal, buffer);
	if (!clip.ptr)
		return (1);
	string_clear(terminal->clipboard);
	string_append_n(terminal->clipboard, clip.ptr, clip.size);
	return (1);
}

int		terminal_paste(t_terminal *terminal, int c)
{
	c = 0;
	while (terminal->clipboard->buffer[c])
		terminal_insert(terminal, terminal->clipboard->buffer[c++]);
	return (1);
}
