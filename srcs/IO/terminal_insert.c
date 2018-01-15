/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 14:41:58 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		terminal_insert(t_terminal *terminal, int c)
{
	int	i;

	terminal_command(INSERT, 1);
	write(terminal->tty, &c, 1);
	i = get_letter_index(terminal);
	i = 0;
	if (!string_insert(terminal->line, c,
				terminal->cursor - terminal->prompt_size - i))
		return (-1);
	terminal->cursor++;
	return (1);
}

int		terminal_insert_string(t_terminal *terminal, char *str)
{
	int	i;
	int	j;

	terminal_command(INSERT, 1);
	ft_dprintf(terminal->tty, "%s", str);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!string_insert(terminal->line, str[i],
					terminal->cursor - terminal->prompt_size - j))
			return (-1);
		++(terminal->cursor);
		++i;
	}
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	if (terminal->line->buffer[terminal->cursor - terminal->prompt_size]
			== '\\')
		return (terminal_insert(terminal, c));
	write(terminal->tty, &c, 1);
	return (0);
}

int		terminal_noop(t_terminal *terminal, int c)
{
	(void)terminal;
	(void)c;
	return (1);
}
