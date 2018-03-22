/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:11:12 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/22 14:20:40 by ccabral          ###   ########.fr       */
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
	&terminal_previous_word,
	&terminal_kill_line,
	&terminal_exit,
	&terminal_eol,
	&terminal_next_word,
	&terminal_noop,
	&terminal_delete,
	&auto_complete,
	&terminal_eof,
	&terminal_delete_until_eol,
	&terminal_noop,
	&terminal_eof,
	&history_next,
	&terminal_eof,
	&history_previous,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_paste,
	&terminal_noop,
	&terminal_delete_word,
	&terminal_noop,
	&terminal_copy,
	&terminal_noop,
	&terminal_escape,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_noop,
	&terminal_insert,
	&terminal_insert,
	&terminal_quotes,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
	&terminal_quotes,
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
	&terminal_backslash,
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
	&terminal_delete,
	&terminal_insert,
	&terminal_insert,
	&terminal_insert,
};

int			large_input(t_terminal *terminal, char c[16])
{
	int	i;
	int	ret;

	if ((*c & 0x60) || (*c & 0x70) || (*c & 0x78) || (*c & 0x7c))
		return (terminal_insert_string(terminal, c));
	i = 0;
	ret = -1;
	while (c[i])
	{
		if (c[i] >= 0)
			ret = handle_input(terminal, c + i, 1);
		++i;
	}
	return (ret);
}

int			handle_string_input(t_terminal *terminal, char c[16])
{
	if (terminal_compare_string(ARROW_UP, c))
		return (history_previous(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_DOWN, c))
		return (history_next(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_RIGHT, c))
		return (terminal_move_right(terminal, (int)c[0]));
	else if (terminal_compare_string(ARROW_LEFT, c))
		return (terminal_move_left(terminal, (int)c[0]));
	else if (terminal_compare_string(CTRL_ARROW_UP, c))
		return (history_previous(terminal, (int)c[0]));
	else if (terminal_compare_string(CTRL_ARROW_DOWN, c))
		return (history_next(terminal, (int)c[0]));
	else if (terminal_compare_string(CTRL_ARROW_RIGHT, c))
		return (terminal_next_word(terminal, (int)c[0]));
	else if (terminal_compare_string(CTRL_ARROW_LEFT, c))
		return (terminal_previous_word(terminal, (int)c[0]));
	else if (terminal_compare_string(DELETE_KEY, c))
		return (terminal_delete_current(terminal, 0));
	else if (terminal_compare_string(HOME, c))
		return (terminal_bol(terminal, 0));
	else if (terminal_compare_string(END, c))
		return (terminal_eol(terminal, 0));
	if (c[0] == '\e')
		return (dispatch_escape_string(terminal, c));
	return (large_input(terminal, c));
}

int			handle_escpape_input(t_terminal *terminal, char c[16], int size)
{
	(void)terminal;
	(void)c;
	(void)size;
	return (1);
}

int			handle_regular_input(t_terminal *terminal, int c)
{
	return (g_key_map[c](terminal, c));
}

int			handle_input(t_terminal *terminal, char c[16], int size)
{
	if (terminal->input_mode == NORMAL_INPUT
			|| terminal->input_mode == QUOTE_INPUT
			|| terminal->input_mode == HEREDOC_INPUT)
	{
		if (size > 1 || (unsigned char)c[0] >= 128)
			return (handle_string_input(terminal, c));
		return (g_key_map[(int)*c](terminal, *c));
	}
	else if (terminal->input_mode == BACKSLASH_INPUT)
		return (terminal_backslash_input(terminal, c, size));
	else if (terminal->input_mode == ESCAPE_INPUT)
	{
		ft_memmove(c + sizeof(char), c, size);
		c[0] = '\e';
		terminal->input_mode = NORMAL_INPUT;
		return (handle_string_input(terminal, c));
	}
	return (1);
}
