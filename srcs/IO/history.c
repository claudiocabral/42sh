/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:52:09 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/11 17:00:10 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int						history_previous(t_terminal *terminal, int c)
{
	(void)c;
	terminal_bol(terminal, 0);
	terminal_delete_until_eol(terminal, 0);
	string_copy(terminal->line,
			(t_string *)ring_buffer_previous(terminal->history));
	terminal_command(INSERT, terminal->line->size);
	write(terminal->tty, terminal->line->buffer, terminal->line->size);
	terminal->cursor += terminal->line->size;
	return (1);
}

int						history_next(t_terminal *terminal, int c)
{
	(void)c;
	terminal_bol(terminal, 0);
	terminal_delete_until_eol(terminal, 0);
	string_copy(terminal->line,
			(t_string *)ring_buffer_next(terminal->history));
	terminal_command(INSERT, terminal->line->size);
	write(terminal->tty, terminal->line->buffer, terminal->line->size);
	terminal->cursor += terminal->line->size;
	return (1);
}
