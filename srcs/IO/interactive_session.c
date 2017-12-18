/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/18 14:56:18 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <shellma.h>
#include <signal_handlers.h>
#include <signal.h>
#include <term.h>
#include <io.h>

void				quit(void)
{
	t_terminal	*terminal;

	terminal = get_terminal(0);
	write(terminal->tty, "\n", 1);
	free_terminal(terminal);
	exit(0);
}


static char	const *prompt(t_terminal *terminal)
{
	size_t		size;
	char		c[16];

	ring_buffer_push_empty(terminal->history);
	terminal->line = (t_string*)terminal->history->current;
	termios_toggle_isig(terminal, 0);
	ft_printf("%s", terminal->prompt);
	while ((size = read(terminal->tty, c, 15)))
	{
		c[size] = 0;
		if (handle_input(terminal, c) == 0)
			break ;
	}
	termios_toggle_isig(terminal, 1);
	terminal->cursor = terminal->prompt_size;
	return (terminal->line->buffer);
}

void		interactive_session(void)
{
	t_terminal	terminal;

	if (!setup_terminal(&terminal, "$> "))
		exit(1);
	while (1)
		process_input(prompt(&terminal));
}
