/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_line_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:34:18 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:34:59 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int		terminal_bol(t_terminal *terminal, int c)
{
	terminal_command(HIDE_CURSOR, 0);
	while (terminal->cursor)
		terminal_move_left(terminal, c);
	terminal_command(SHOW_CURSOR, 0);
	return (1);
}

int		terminal_eol(t_terminal *terminal, int c)
{
	terminal_command(HIDE_CURSOR, 0);
	while ((unsigned long)terminal->cursor !=
			terminal->line->size)
		terminal_move_right(terminal, c);
	terminal_command(SHOW_CURSOR, 0);
	return (1);
}

int		is_at_newline(t_terminal *terminal, int index)
{
	return (terminal->line->buffer[index - 1] == '\n'
			|| (index != 0
				&& get_position_in_line(terminal, index)
				== get_terminal_width()));
}

int		terminal_is_at_newline(t_terminal *terminal)
{
	return (is_at_newline(terminal, terminal->cursor));
}
