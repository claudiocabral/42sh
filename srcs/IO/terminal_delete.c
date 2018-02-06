/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_delete.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:50:47 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/06 11:25:36 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_printf.h>
#include <io.h>

int		terminal_adjust_delete(t_terminal *terminal, int index, int column)
{
	int		next;
	int		width;

	width = get_terminal_width();
	terminal_command(MOVE_RIGHT, width - column);
	write(STDIN_FILENO, terminal->line->buffer + index++, 1);
	terminal_command(MOVE_DOWN, 1);
	terminal_command(MOVE_LEFT, width - 1);
	terminal_command(DELETE, 1);
	while (is_middle_of_unicode(terminal->line->buffer[index]))
		write(STDIN_FILENO, terminal->line->buffer + index++, 1);
	if ((next = line_overflow(terminal, index + 1, 1, width - 1)))
		terminal_adjust_delete(terminal, next, 1);
	terminal_command(MOVE_UP, 1);
	return (1);
}

void					terminal_delete_position_cursor(t_terminal *terminal,
																		int c)
{
	int	column;
	int	width;
	int	index;

	c = 8;
	(void)index;
	column = get_position_in_line(terminal, terminal->cursor);
	width = get_terminal_width();
	if (column == width)
	{
		terminal_command(MOVE_UP, 1);
		terminal_command(MOVE_RIGHT, get_terminal_width() - 1);
		if ((index = line_overflow(terminal, terminal->cursor, column, width)))
			write(STDIN_FILENO, terminal->line->buffer + index, 1);
		else
			write(STDIN_FILENO, " ", 1);
	}
	else
		write(STDIN_FILENO, &c, 1);
}

int						terminal_delete(t_terminal *terminal, int c)
{
	int	column;
	int	index;
	int	width;

	if (!terminal->cursor)
		return (1);
	terminal_delete_position_cursor(terminal, c);
	terminal_command(DELETE, 1);
	while (is_middle_of_unicode(
				terminal->line->buffer[terminal->cursor - 1]))
	{
		string_delete(terminal->line, terminal->cursor - 1);
		terminal->cursor--;
	}
	string_delete(terminal->line, terminal->cursor - 1);
	terminal->cursor--;
	column = get_position_in_line(terminal, terminal->cursor);
	width = get_terminal_width();
	if (column != width &&
			(index = line_overflow(terminal, terminal->cursor, column, width - 1)))
	{
		terminal_adjust_delete(terminal, index, column);
		terminal_command(MOVE_RIGHT, column);
	}
	return (1);
}

int						terminal_delete_current(t_terminal *terminal, int c)
{
	if ((unsigned int)terminal->cursor
			>= terminal->line->size)
		return (1);
	terminal_move_right(terminal, c);
	terminal_delete(terminal, c);
	return (1);
}

int						terminal_delete_word(t_terminal *terminal, int c)
{
	while (terminal->cursor &&
			ft_is_whitespace(terminal->line->buffer [terminal->cursor - 1]))
		terminal_delete(terminal, c);
	while (terminal->cursor &&
			!ft_is_whitespace(terminal->line->buffer [terminal->cursor - 1]))
		terminal_delete(terminal, c);
	return (1);
}

int						terminal_delete_until_eol(t_terminal *terminal, int c)
{
	int		current_position;

	current_position = terminal->cursor;
	terminal_eol(terminal, c);
	while (terminal->cursor > current_position)
		terminal_delete(terminal, c);
	return (1);
}

int						terminal_kill_line(t_terminal *terminal, int c)
{
	(void)c;
	terminal_eol(terminal, 0);
	write(0, "\n", 1);
	string_clear(terminal->line);
	print_prompt(terminal);
	terminal->cursor = 0;
	return (1);
}
