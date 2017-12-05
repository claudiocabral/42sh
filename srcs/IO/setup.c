/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:10:44 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 22:26:17 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal_handlers.h>
#include <signal.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <libft.h>
#include <term.h>
#include <io.h>

void				set_termios(struct termios *termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, termios);
}

void				free_terminal(t_terminal *terminal)
{
	free(terminal->prompt);
	string_free(terminal->line);
	ring_buffer_free(terminal->history, (t_freef)&string_free);
	terminal->prompt = 0;
	terminal->line = 0;
	terminal->history = 0;
}

static void			init_termios(t_terminal *terminal)
{
	tcgetattr(0, &(terminal->original));
	terminal->custom = terminal->original;
	terminal->custom.c_lflag &= ~(ECHO | ICANON);
	terminal->custom.c_oflag &= (OPOST | ONLCR);
	terminal->custom.c_cc[VMIN] = 1;
	terminal->custom.c_cc[VTIME] = 0;
	set_termios(&(terminal->custom));
}

int					setup_terminal(t_terminal *terminal, char const *prompt)
{
	signal(SIGINT, (void (*)(int))&interrupt_handler);
	if (!tgetent(0, getenv("TERM")))
		return (0);
	init_command_table();
	terminal->prompt = 0;
	terminal->line = 0;
	terminal->history = 0;
	init_termios(terminal);
	terminal->prompt = ft_strdup(prompt);
	terminal->line = string_create(STRING_SIZE);
	terminal->history = ring_buffer_create(sizeof(t_string), 2000,
													(t_freef)&string_clear);
	ring_buffer_init(terminal->history, STRING_SIZE,
			(void *(*)(void *, size_t))&string_init, (t_freef)&string_free);
	terminal->tty = 0;
	if (!terminal->prompt || !terminal->line || !terminal->history)
	{
		free_terminal(terminal);
		return (0);
	}
	terminal->prompt_size = ft_strlen(prompt);
	terminal->cursor = terminal->prompt_size;
	return (1);
}
