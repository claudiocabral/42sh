/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/04 22:03:53 by claudioca        ###   ########.fr       */
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

int						is_last_line(t_terminal *terminal, int line)
{
	return (get_line(terminal, terminal->line->size) == line);
}

int		line_size(t_terminal *terminal, int index)
{
	int	i;
	int	j;

	i = 0;
	j = terminal->prompt_size;
	while (terminal->line->buffer[i] && i < index)
	{
		if (is_at_newline(terminal, i))
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
			++j;
		++i;
	}
	if (terminal->line->buffer[i] == '\n')
		++i;
	return (i);
}

int		line_overflow(t_terminal *terminal, int index)
{
	return (line_size(terminal, index) == get_terminal_width()
			&& !is_last_line(terminal, get_line(terminal, index)));
}

int		terminal_insert(t_terminal *terminal, int c)
{
	if (!string_insert(terminal->line, c,
				terminal->cursor))
		return (-1);
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, &c, 1);
	terminal->cursor++;
	if (get_position_in_line(terminal, terminal->cursor) == get_terminal_width())
		write(STDIN_FILENO, "\n", 1);
	else if (line_overflow(terminal, terminal->cursor))
		terminal_adjust(terminal, terminal->cursor);
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


int						terminal_adjust(t_terminal *terminal, int index)
{
	int		column;
	int		line;
	int		c;

	column = get_position_in_line(terminal, index);
	line = get_line(terminal, index);
	c = get_first_in_line(terminal, line + 1) - 1;
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
	++c;
	if (line_size(terminal, c) > get_terminal_width())
	{
		ft_printf("\nthis is fuckedup index is %d and line size is %d\n",
				c, line_size(terminal, c));
		terminal_adjust(terminal, c);
	}
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
