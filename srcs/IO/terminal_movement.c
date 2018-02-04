/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 09:19:57 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/04 22:00:36 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_string.h>
#include <unistd.h>

int		terminal_bol(t_terminal *terminal, int c)
{
	while (terminal->cursor)
		terminal_move_left(terminal, c);
	return (1);
}

int		terminal_eol(t_terminal *terminal, int c)
{
	while ((unsigned long)terminal->cursor !=
			terminal->line->size)
		terminal_move_right(terminal, c);
	return (1);
}

int		is_at_newline(t_terminal *terminal, int index)
{

	return (terminal->line->buffer[index] == '\n'
			|| (index != 0
				&& get_position_in_line(terminal, index) == get_terminal_width()));
}

int		terminal_is_at_newline(t_terminal *terminal)
{
	return (is_at_newline(terminal, terminal->cursor));
}

int		terminal_adjust_cursor(t_terminal * terminal, int from, int to)
{
	int	direction;
	int	movement;

	if (from > to)
	{
		direction = -1;
		movement = MOVE_LEFT;
	}
	else
	{
		direction = 1;
		movement = MOVE_RIGHT;
	}
	while (from >= 0
			&& terminal->line->buffer[from]
			&& terminal->line->buffer[from] != '\n'
			&& from != to)
	{
		from += direction;
		while (is_middle_of_unicode(terminal->line->buffer[from]))
			from += direction;
		terminal_command(movement, 1);
	}
	return (1);
}

int		terminal_move_left(t_terminal *terminal, int c)
{
	(void)c;
	if (!terminal->cursor)
		return (1);
	terminal->cursor--;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor--;
	if (terminal_is_at_newline(terminal))
	{
		if (terminal->line->buffer[terminal->cursor] == '\n')
			terminal->cursor--;
		terminal_command(MOVE_UP, 1);
		terminal_adjust_cursor(terminal, 0,
				get_position_in_line(terminal, terminal->cursor));
	}
	else
		terminal_command(MOVE_LEFT, 1);
	return (1);
}

int		terminal_move_right(t_terminal *terminal, int c)
{
	if ((unsigned int)terminal->cursor
			>= terminal->line->size)
		return (1);
	c = get_position_in_line(terminal, terminal->cursor);
	terminal->cursor++;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor++;
	if (terminal_is_at_newline(terminal))
	{
		if (terminal->line->buffer[terminal->cursor] == '\n')
			terminal->cursor++;
		terminal_command(MOVE_DOWN, 1);
		terminal_adjust_cursor(terminal, c, 0);
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
		if (terminal->line->buffer[i] == '\n'
				|| j >= get_terminal_width())
			j = 0;
		else
			++j;
		++i;
	}
	return (j);
}
