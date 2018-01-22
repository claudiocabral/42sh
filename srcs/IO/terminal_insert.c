/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 18:25:47 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		terminal_insert(t_terminal *terminal, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (j < terminal->line_number)
	{
		if (terminal->line->buffer[i] == '\n')
			++j;
		++i;
	}
	if (!string_insert(terminal->line, c,
				terminal->cursor + i))
		return (-1);
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, &c, 1);
	terminal->cursor++;
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
	terminal_command(INSERT, terminal->line->size);
	write(STDIN_FILENO, terminal->line->buffer, terminal->line->size);
	c = 0;
	while (terminal->line->buffer[c])
	{
		if (terminal->line->buffer[c] == '\n')
		{
			++(terminal->line_number);
			terminal->cursor = 0;
		}
		else
			++(terminal->cursor);
		++c;
	}
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
