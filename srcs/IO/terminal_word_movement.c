/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_word_movement.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:28:33 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 17:29:09 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int						terminal_begining(t_terminal *terminal, int c)
{
	(void)c;
	if (terminal->line_number)
		terminal_command(MOVE_UP, terminal->line_number);
	terminal_command(MOVE_LEFT, get_terminal_width());
	terminal_command(CLEAR_BOTTOM, 0);
	terminal->line_number = 0;
	return (1);
}

int						terminal_previous_word(t_terminal *terminal, int c)
{
	int	tmp;

	while (terminal->cursor
			&& ft_is_whitespace(terminal->line->buffer[terminal->cursor - 1]))
	{
		tmp = terminal->cursor;
		terminal_move_left(terminal, c);
		if (tmp == terminal->cursor)
			return (1);
	}
	while (terminal->cursor
			&& !ft_is_whitespace(terminal->line->buffer[terminal->cursor - 1]))
	{
		tmp = terminal->cursor;
		terminal_move_left(terminal, c);
		if (tmp == terminal->cursor)
			return (1);
	}
	return (1);
}

int						terminal_next_word(t_terminal *terminal, int c)
{
	while (terminal->cursor != (int)terminal->line->size
			&& !ft_is_whitespace(terminal->line->buffer[terminal->cursor]))
		terminal_move_right(terminal, c);
	while (terminal->cursor != (int)terminal->line->size
			&& ft_is_whitespace(terminal->line->buffer[terminal->cursor]))
		terminal_move_right(terminal, c);
	return (1);
}
