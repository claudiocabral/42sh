/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/20 15:17:25 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		line_overflow(t_terminal *terminal, int index, int column, int target)
{
	while (terminal->line->buffer[index]
			&& terminal->line->buffer[index] != '\n')
	{
		if (column == target)
			return (index);
		++index;
		++column;
	}
	return (0);
}

int		terminal_insert(t_terminal *terminal, int c)
{
	int	column;
	int	index;
	int	width;

	if (!string_insert(terminal->line, c,
				terminal->cursor))
		return (-1);
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, &c, 1);
	terminal->cursor++;
	column = get_position_in_line(terminal, terminal->cursor);
	width = get_terminal_width();
	if ((index = line_overflow(terminal, terminal->cursor, column, width)))
	{
		terminal_adjust_insert(terminal, index, column);
		terminal_command(MOVE_RIGHT, column - 1);
	}
	if (column == width)
		write(STDIN_FILENO, "\n", 1);
	return (1);
}

int		terminal_insert_string(t_terminal *terminal, char *str)
{
	int	i;

	terminal_command(INSERT, 1);
	ft_dprintf(STDIN_FILENO, "%s", str);
	i = 0;
	while (str[i])
	{
		if (!string_insert(terminal->line, str[i],
					terminal->cursor))
			return (-1);
		++(terminal->cursor);
		++i;
	}
	return (1);
}

int		terminal_adjust_insert(t_terminal *terminal, int index, int column)
{
	int		next;
	int		width;

	width = get_terminal_width();
	if ((unsigned long)index == terminal->line->size - 1)
	{
		terminal_command(MOVE_RIGHT, width - column);
		write(STDIN_FILENO, "\n", 1);
	}
	else
	{
		terminal_command(MOVE_LEFT, column);
		terminal_command(MOVE_DOWN, 1);
	}
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, terminal->line->buffer + index++, 1);
	while (is_middle_of_unicode(terminal->line->buffer[index]))
		write(STDIN_FILENO, terminal->line->buffer + index++, 1);
	if ((next = line_overflow(terminal, index + 1, 2, width)))
		terminal_adjust_insert(terminal, next, 2);
	terminal_command(MOVE_UP, 1);
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	int	ret;

	ret = 0;
	if (terminal->line->buffer[terminal->cursor]
			== '\\')
		return (terminal_insert(terminal, c));
	else if (terminal->input_mode == HEREDOC_INPUT)
		return (0);
	else if (terminal->input_mode != HEREDOC_INPUT)
		ret = collect_heredocs(terminal);
	write(STDIN_FILENO, &c, 1);
	return (ret);
}
