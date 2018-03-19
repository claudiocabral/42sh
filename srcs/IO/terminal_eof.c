/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:32:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:33:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int		terminal_noop(t_terminal *terminal, int c)
{
	(void)terminal;
	(void)c;
	return (1);
}

int		terminal_write(t_terminal *terminal, int c)
{
	(void)c;
	terminal_command(INSERT, terminal->line->size);
	write(STDIN_FILENO, terminal->line->buffer, terminal->line->size);
	return (1);
}
