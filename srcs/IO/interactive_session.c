/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 23:00:31 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <shellma.h>
#include <signal_handlers.h>
#include <term.h>
#include <io.h>

void		quit(t_terminal *terminal)
{
		set_termios(&(terminal->original));
		free(terminal->prompt);
		exit(0);
}

void		terminal_BOL(t_terminal *terminal)
{
	terminal_command_params(MOVE_LEFT, 0, terminal->cursor
										- terminal->prompt_size);
	terminal->cursor = terminal->prompt_size;
}

static char	const *prompt(t_terminal *terminal)
{
	int		i;
	char	c;

	ft_printf("%s", terminal->prompt);
	i = 0;
	while (read(terminal->tty, &c, 1))
	{
		if (handle_input(terminal, c) == 0)
			break ;
	}
	ring_buffer_push_back(terminal->history, terminal->line,
			(void*(*)(void *, void const *))&string_copy);
	string_clear(terminal->line);
	terminal->cursor = terminal->prompt_size;
	return (((t_string*)terminal->history->current)->buffer);
}

void		interactive_session(void)
{
	t_terminal	terminal;

	setup_terminal(&terminal, "$> ");
	while (1)
		execute(parse(lex(prompt(&terminal))));
}
