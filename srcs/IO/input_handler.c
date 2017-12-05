/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/04 12:11:12 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 23:01:29 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shellma.h>
#include <io.h>
#include <unistd.h>
#include <signal_handlers.h>
#include <stdlib.h>

typedef int				(*input_handle_t)(t_terminal *, char c);

int						insert_and_display(t_terminal *terminal, char c)
{
	write(terminal->tty, &c, 1);
	if (c == '\n')
		return (0);
	if (!string_insert(terminal->line, c,
				terminal->cursor - terminal->prompt_size))
		return (0);
	++(terminal->cursor);
	return (1);
}

static input_handle_t	g_key_map[] =
{
	&insert_and_display
};

int			handle_input(t_terminal *terminal, char c)
{
	if (interrupt_handler(0))
		quit(terminal);
	g_key_map[0](terminal, c);
	if (c == '\n')
		return (0);
	return (1);
}
