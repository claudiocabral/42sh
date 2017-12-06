/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:11:12 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/06 17:28:03 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <shellma.h>
#include <io.h>
#include <signal_handlers.h>
#include <ring_buffer.h>

typedef int				(*input_handle_t)(t_terminal *, int character);


int						terminal_insert(t_terminal *terminal, int c)
{
	terminal_command(INSERT, 1);
	write(terminal->tty, &c, 1);
	if (!string_insert(terminal->line, c,
				terminal->cursor - terminal->prompt_size))
		return (-1);
	++(terminal->cursor);
	return (1);
}

int						terminal_EOF(t_terminal *terminal, int c)
{
	if (terminal->line->buffer[terminal->cursor - terminal->prompt_size] == '\\')
		return (terminal_insert(terminal, c));
	write(terminal->tty, &c, 1);
	return (0);
}

int						terminal_exit(t_terminal *terminal, int c)
{
	(void)c;
	(void)terminal;
	quit();
	return (1);
}

int						terminal_delete(t_terminal *terminal, int c)
{
	c = CTRL_H;
	if (terminal->cursor == terminal->prompt_size)
		return (1);
	write(terminal->tty, &c, 1);
	terminal_command(DELETE, 1);
	string_delete(terminal->line, terminal->cursor - terminal->prompt_size - 1);
	--(terminal->cursor);
	return (1);
}

#include <ft_printf.h>
int						terminal_delete_word(t_terminal *terminal, int c)
{
	(void)c;
	if (terminal->cursor == terminal->prompt_size)
		return (1);
	while (ft_is_whitespace(terminal->line->buffer
			[terminal->cursor - terminal->prompt_size - 1])
			&& terminal->cursor != terminal->prompt_size)
		terminal_delete(terminal, c);
	while (!ft_is_whitespace(terminal->line->buffer
			[terminal->cursor - terminal->prompt_size - 1])
			&& terminal->cursor != terminal->prompt_size)
		terminal_delete(terminal, c);
	return (1);
}

int						terminal_delete_until_EOL(t_terminal *terminal, int c)
{
	int	current_position;

	current_position = terminal->cursor;
	terminal_EOL(terminal, c);
	while (terminal->cursor > current_position)
		terminal_delete(terminal, CTRL_H);
	return (1);
}

int						history_previous(t_terminal *terminal, int c)
{
	(void)c;
	terminal_BOL(terminal, 0);
	terminal_delete_until_EOL(terminal, 0);
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
	terminal_BOL(terminal, 0);
	terminal_delete_until_EOL(terminal, 0);
	string_copy(terminal->line,
			(t_string *)ring_buffer_next(terminal->history));
	terminal_command(INSERT, terminal->line->size);
	write(terminal->tty, terminal->line->buffer, terminal->line->size);
	terminal->cursor += terminal->line->size;
	return (1);
}

static input_handle_t	g_key_map[256] =
{
	&terminal_insert,
	&terminal_BOL,
	&history_previous,
	&terminal_exit,
	&terminal_exit,
	&terminal_EOL,
	&terminal_insert,
	&terminal_insert,
	&terminal_delete,
	&terminal_insert,
	&terminal_EOF,
	&terminal_delete_until_EOL,
	&terminal_EOF,
	&terminal_EOF,
	&history_next,
	&terminal_EOF,
	&history_previous,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_delete_word,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
};

int			handle_input(t_terminal *terminal, int c)
{
	if (interrupt_handler(0))
		quit();
	g_key_map[c](terminal, c);
	if (c == '\n')
		return (0);
	return (1);
}
