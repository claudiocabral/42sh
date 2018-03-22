/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:54:15 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 16:55:11 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <io.h>

void	history_cleanup(t_terminal *terminal, int save)
{
	terminal->buffer_size = 16;
	close(terminal->history_fd);
	dup2(save, STDIN_FILENO);
	close(save);
	terminal->history_fd = 0;
	terminal->fd = STDIN_FILENO;
}
