/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:09:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/05 09:59:11 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <io.h>
#include <sys/ioctl.h>

#include <ft_printf.h>
int	get_terminal_width(void)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	return (ws.ws_col == 0 ? 1 : ws.ws_col);
}

int	get_terminal_height(void)
{
	int	height;

	height = tgetnum("li");
	return (height == 0 ? 1 : height);
}
