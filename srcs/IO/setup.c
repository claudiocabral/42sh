/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:10:44 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 19:17:49 by ccabral          ###   ########.fr       */
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
#include <environment.h>

void				termios_toggle_isig(t_terminal *term, int toggle)
{
	if (toggle)
		term->custom.c_lflag |= ISIG;
	else
		term->custom.c_lflag &= ~(ISIG);
	set_termios(&(term->custom));
}

void				set_termios(struct termios *termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, termios);
}

void				free_terminal(t_terminal *terminal)
{
	ring_buffer_free(terminal->history, (t_freef) & string_free_content);
	terminal->line = 0;
	terminal->history = 0;
}

static void			init_termios(t_terminal *terminal)
{
	terminal->width = tgetnum("co");
	terminal->height = tgetnum("li");
	tcgetattr(0, &(terminal->original));
	terminal->custom = terminal->original;
	terminal->custom.c_iflag |= ICRNL;
	terminal->custom.c_lflag &= ~(ECHO | ICANON | ECHOE | ECHOKE
			| ECHOCTL);
	terminal->custom.c_oflag &= (OPOST | ONLCR);
	terminal->custom.c_cc[VMIN] = 1;
	terminal->custom.c_cc[VTIME] = 0;
	terminal->custom.c_cc[VERASE] = CTRL_H;
	set_termios(&(terminal->custom));
}

int					setup_terminal(t_terminal *terminal, char const *prompt)
{
	signal(SIGINT, (void (*)(int))&interrupt_handler);
	if (tgetent(0, ttyname(ttyslot())) <= 0)
	{
		ft_dprintf(2, "./minishell: Could not set terminal type\n"
				"Terminating...\n");
		return (0);
	}
	init_command_table();
	terminal->history = 0;
	init_termios(terminal);
	ft_strcpy(terminal->prompt, prompt);
	terminal->history = ring_buffer_create(sizeof(t_string), 2000,
			(t_freef) & string_clear);
	ring_buffer_init(terminal->history, STRING_SIZE,
		(void *(*)(void *, size_t)) &string_init, (t_freef) & string_free);
	terminal->tty = 0;
	if (!terminal->history)
	{
		free_terminal(terminal);
		return (0);
	}
	terminal->prompt_size = ft_strlen(prompt);
	terminal->cursor = terminal->prompt_size;
	return (1);
}
