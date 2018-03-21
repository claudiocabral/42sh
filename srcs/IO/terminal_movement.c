/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 09:19:57 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/21 13:03:46 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_string.h>
#include <unistd.h>

int		terminal_adjust_cursor(int from, int to)
{
	int	direction;
	int	movement;

	if (from > to)
	{
		direction = from - to;
		movement = MOVE_LEFT;
	}
	else
	{
		direction = to - from;
		movement = MOVE_RIGHT;
	}
	terminal_command(movement, direction);
	return (1);
}

int		terminal_move_left(t_terminal *terminal, int c)
{
	if (!terminal->cursor
			|| terminal->line->buffer[terminal->cursor - 1] == '\n')
		return (1);
	if (terminal_is_at_newline(terminal))
	{
		terminal_command(MOVE_UP, 1);
		c = terminal->line->buffer[terminal->cursor - 1] == '\n';
		terminal_adjust_cursor(0,
				get_position_in_line(terminal, terminal->cursor - c));
	}
	else
		terminal_command(MOVE_LEFT, 1);
	terminal->cursor--;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor--;
	return (1);
}

int		terminal_move_right(t_terminal *terminal, int c)
{
	if ((unsigned int)terminal->cursor
			>= terminal->line->size)
		return (1);
	terminal->cursor++;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor++;
	c = get_position_in_line(terminal, terminal->cursor);
	if (terminal_is_at_newline(terminal))
	{
		if (terminal->line->buffer[terminal->cursor] == '\n')
			terminal->cursor++;
		terminal_command(MOVE_DOWN, 1);
		terminal_adjust_cursor(c, 1);
	}
	else
		terminal_command(MOVE_RIGHT, 1);
	return (1);
}

int		terminal_exit(t_terminal *terminal, int c)
{
	(void)c;
	if (terminal->line->size == 0)
		quit(terminal);
	terminal_delete_current(terminal, c);
	return (1);
}

int		get_position_in_line(t_terminal *terminal, int index)
{
	int	i;
	int	j;

	i = 0;
	j = terminal->prompt_size;
	while (i < index)
	{
		if ((terminal->line->buffer[i] == '\n'
				|| j > get_terminal_width()))
			j = 1;
		++j;
		++i;
	}
	return (j);
}
