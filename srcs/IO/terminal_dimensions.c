/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:09:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/19 14:19:05 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <io.h>
#include <sys/ioctl.h>

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
