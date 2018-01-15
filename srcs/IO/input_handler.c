/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:11:12 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 14:43:25 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <shellma.h>
#include <io.h>
#include <signal_handlers.h>
#include <ring_buffer.h>
#include <ft_printf.h>

static t_input_handle	g_key_map[256] =
{
	&terminal_insert,
	&terminal_bol,
	&history_previous,
	&terminal_kill_line,
	&terminal_exit,
	&terminal_eol,
	&terminal_noop,
	&terminal_noop,
	&terminal_delete,
	&auto_complete,
	&terminal_eof,
	&terminal_delete_until_eol,
	&terminal_eof,
	&terminal_eof,
	&history_next,
	&terminal_eof,
	&history_previous,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_delete_word,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
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
	&terminal_noop,
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
	&terminal_delete,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
};

int			handle_string_input(t_terminal *terminal, char c[16])
{
	if (terminal_compare_string(ARROW_UP, c))
		return (history_previous(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_DOWN, c))
		return (history_next(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_LEFT, c))
		return (terminal_move_left(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_RIGHT, c))
		return (terminal_move_right(terminal, (int)c[0]));
	else if (terminal_compare_string(DELETE_KEY, c))
		return (terminal_delete(terminal, CTRL_H));
	terminal_insert_string(terminal, c);
	return (1);
}

int			handle_input(t_terminal *terminal, char c[16])
{
	if (c[1] != 0 || (unsigned char)c[0] >= 128)
		return (handle_string_input(terminal, c));
	return (g_key_map[(int)c[0]](terminal, c[0]));
}
