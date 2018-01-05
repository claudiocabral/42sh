/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 11:24:24 by claudioca        ###   ########.fr       */
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
#include <environment.h>
#include <io.h>

void				quit(void)
{
	t_terminal	*terminal;

	terminal = get_terminal(0);
	write(terminal->tty, "\n", 1);
	free_terminal(terminal);
	exit(0);
}

void				print_prompt(t_terminal *terminal)
{
	char const	*path;

	path = ft_getenv("PWD");
	if (ft_strcmp(path, "/"))
	{
		path = path ? ft_strrchr(path, '/') : 0 ;
		path = path ? path + 1 : 0 ;
	}
	terminal->prompt_size = ft_printf("%s%c%s", path ? path : "",
												path ? ' ' : 0,
												terminal->prompt);
	terminal->cursor = terminal->prompt_size;
}

static char	const	*prompt(t_terminal *terminal)
{
	size_t		size;
	char		c[16];

	ring_buffer_push_empty(terminal->history);
	terminal->line = (t_string*)terminal->history->current;
	termios_toggle_isig(terminal, 0);
	print_prompt(terminal);
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
