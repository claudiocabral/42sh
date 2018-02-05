/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/05 12:40:05 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		get_line(t_terminal *terminal, int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (terminal->line->buffer[i] && i < index)
	{
		if (is_at_newline(terminal, i))
			++j;
		++i;
	}
	return (j);
}

int		line_size(t_terminal *terminal, int index)
{
	int	i;
	int	j;

	i = 0;
	j = terminal->prompt_size;
	while (terminal->line->buffer[i] && i < index)
	{
		if (j >= get_terminal_width())
			j = 0;
		else
			++j;
		++i;
	}
	while (terminal->line->buffer[i] && !is_at_newline(terminal, i))
	{
		++i;
		++j;
	}
	if (terminal->line->buffer[i])
		++j;
	return (j);
}


int		get_last_in_line(t_terminal *terminal, int line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (terminal->line->buffer[i] && j < line)
	{
		if (is_at_newline(terminal, i))
			++j;
		++i;
	}
	while (terminal->line->buffer[i] && !is_at_newline(terminal, i))
		++i;
	return (i);
}

int		get_first_in_line(t_terminal *terminal, int line)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (terminal->line->buffer[i] && j < line)
	{
		if (is_at_newline(terminal, i))
		{
			++j;
			if (j == line)
				break ;
		}
		++i;
	}
	return (i);
}

int		line_overflow(t_terminal *terminal, int index, int column)
{
	int	width;

	width = get_terminal_width();
	while (terminal->line->buffer[index])
	{
		if (column == width)
			return (index);
		++index;
		++column;
	}
	return (0);
}

int		terminal_insert(t_terminal *terminal, int c)
{
	int	position;
	int	index;

	if (!string_insert(terminal->line, c,
				terminal->cursor))
		return (-1);
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, &c, 1);
	terminal->cursor++;
	position = get_position_in_line(terminal, terminal->cursor);
	if (position == get_terminal_width())
		write(STDIN_FILENO, "\n", 1);
	else if ((index = line_overflow(terminal, terminal->cursor, position)))
		terminal_adjust(terminal, terminal->cursor, index);
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

int						terminal_write(t_terminal *terminal, int c)
{
	(void)c;
	terminal_command(INSERT, terminal->line->size);
	write(STDIN_FILENO, terminal->line->buffer, terminal->line->size);
	return (1);
}

int						recursive_terminal_adjust(t_terminal *terminal,
														int c)
{
	int		column;

	column = 2;
	if ((unsigned long)c == terminal->line->size - 1)
	{
		terminal_command(MOVE_RIGHT, get_terminal_width() - column);
		write(STDIN_FILENO, "\n", 1);
	}
	else
	{
		terminal_command(MOVE_LEFT, column);
		terminal_command(MOVE_DOWN, 1);
	}
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, terminal->line->buffer + c++, 1);
	while (is_middle_of_unicode(terminal->line->buffer[c]))
		write(STDIN_FILENO, terminal->line->buffer + c++, 1);
	if ((column = line_overflow(terminal, c + 1, 2)))
		recursive_terminal_adjust(terminal, column);
	terminal_command(MOVE_UP, 1);
	return (1);

}


int						terminal_adjust(t_terminal *terminal, int index, int c)
{
	int		column;
	int		next;

	column = get_position_in_line(terminal, index);
	if ((unsigned long)c == terminal->line->size - 1)
	{
		terminal_command(MOVE_RIGHT, get_terminal_width() - column);
		write(STDIN_FILENO, "\n", 1);
	}
	else
	{
		terminal_command(MOVE_LEFT, column);
		terminal_command(MOVE_DOWN, 1);
	}
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, terminal->line->buffer + c++, 1);
	while (is_middle_of_unicode(terminal->line->buffer[c]))
		write(STDIN_FILENO, terminal->line->buffer + c++, 1);
	if ((next = line_overflow(terminal, c + 1, 2)))
		recursive_terminal_adjust(terminal, next);
	terminal_command(MOVE_UP, 1);
	terminal_command(MOVE_RIGHT, column - 1);
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	if (terminal->line->buffer[terminal->cursor]
			== '\\')
		return (terminal_insert(terminal, c));
	write(STDIN_FILENO, &c, 1);
	return (0);
}

int		terminal_noop(t_terminal *terminal, int c)
{
	(void)terminal;
	(void)c;
	return (1);
}
