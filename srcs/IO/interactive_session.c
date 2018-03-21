/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_session.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:39:05 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/21 16:23:21 by ccabral          ###   ########.fr       */
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

void				quit(t_terminal *terminal)
{
	termios_toggle_isig(terminal, 1);
	write(STDIN_FILENO, "\n", 1);
	free_terminal(terminal);
	exit(0);
}

void				set_termios(struct termios *termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, termios);
}

int					terminal_get_line(t_terminal *terminal, int fd, int buff_size)
{
	int		size;
	char	c[16];

	while ((size = read(fd, c, buff_size)))
	{
		if (size < 0)
		{
			ft_dprintf(2, "Unknown input error\n");
			handle_input(terminal, "\x03", 1);
			return (size) ;
		}
		c[size] = 0;
		if (handle_input(terminal, c, size) == 0)
			return (0);
		string_copy(terminal->history->current, terminal->line);
	}
	return (1);
}

static char	const	*prompt(t_terminal *terminal)
{
	termios_toggle_isig(terminal, 0);
	set_termios(&(terminal->custom));
	history_load(terminal);
	print_prompt(terminal);
	terminal_get_line(terminal, STDIN_FILENO, 16);
	history_append(terminal);
	string_clear(terminal->line);
	terminal_command(CLEAR_BOTTOM, 0);
	termios_toggle_isig(terminal, 1);
	set_termios(&(terminal->original));
	terminal->cursor = 0;
	terminal->line_number = 0;
	return (((t_string *)terminal->history->current)->buffer);
}

void				interactive_session(void)
{
	t_terminal	terminal;

	if (!setup_terminal(&terminal, "$> "))
		exit(1);
	while (1)
		process_input(prompt(&terminal));
}
