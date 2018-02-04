/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_dimensions.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 12:09:18 by claudioca         #+#    #+#             */
/*   Updated: 2018/02/02 13:08:23 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <termios.h>
#include <io.h>

int	get_terminal_width(void)
{
	int	width;

	width = tgetnum("co");
	return (width == 0 ? 1 : width);
}

int	get_terminal_height(void)
{
	int	height;

	height = tgetnum("li");
	return (height == 0 ? 1 : height);
}
