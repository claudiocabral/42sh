/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/01 10:10:44 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/01 19:02:10 by claudioca        ###   ########.fr       */
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

static t_termios	*g_termios;

void				restore_terminal(t_termios *termios)
{
	tcsetattr(0, TCSANOW, &termios->original);
}

t_termios			*get_termios()
{
	return (g_termios);
}

void				setup_terminal(t_termios *termios)
{
	signal(SIGINT, &interrupt_handler);
	if (!tgetent(0, getenv("TERM")))
		return ;
	g_termios = termios;
	tcgetattr(0, &(termios->original));
	termios->custom = termios->original;
	termios->custom.c_lflag &= ~(ECHO | ICANON);
	termios->custom.c_cc[VMIN] = 1;
	termios->custom.c_cc[VTIME] = 0;
	tcsetattr(STDIN_FILENO, TCSADRAIN, &(termios->custom));
	tputs(tgoto(tgetstr("ce", 0), 40, 40), 1, &ft_putchar);
}
