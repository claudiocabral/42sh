/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 11:15:07 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int						terminal_insert(t_terminal *terminal, int c)
{
	terminal_command(INSERT, 1);
	write(terminal->tty, &c, 1);
	if (!string_insert(terminal->line, c,
				terminal->cursor - terminal->prompt_size))
		return (-1);
	terminal->cursor++;
	return (1);
}

int						terminal_EOF(t_terminal *terminal, int c)
{
	if (terminal->line->buffer[terminal->cursor - terminal->prompt_size] == '\\')
		return (terminal_insert(terminal, c));
	write(terminal->tty, &c, 1);
	return (0);
}
