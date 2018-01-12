/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 09:19:57 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 16:28:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_string.h>
#include <unistd.h>

int		terminal_bol(t_terminal *terminal, int c)
{
	(void)c;
	while (terminal->cursor != terminal->prompt_size)
		terminal_move_left(terminal, c);
	return (1);
}

int		terminal_eol(t_terminal *terminal, int c)
{
	(void)c;
	if ((unsigned long)terminal->cursor
			== terminal->prompt_size + terminal->line->size)
		return (1);
	terminal_command(MOVE_RIGHT, terminal->line->size - terminal->cursor
									+ terminal->prompt_size);
	terminal->cursor = terminal->line->size + terminal->prompt_size;
	return (1);
}

int		terminal_move_left(t_terminal *terminal, int c)
{
	(void)c;
	if (terminal->cursor == terminal->prompt_size)
		return (1);
	terminal_command(MOVE_LEFT, 1);
	terminal->cursor--;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor--;
	return (1);
}

int		terminal_move_right(t_terminal *terminal, int c)
{
	(void)c;
	if ((unsigned int)terminal->cursor
			== terminal->prompt_size + terminal->line->size)
		return (1);
	terminal_command(MOVE_RIGHT, 1);
	terminal->cursor++;
	while (cursor_is_middle_of_unicode(terminal))
		terminal->cursor++;
	return (1);
}

int		terminal_exit(t_terminal *terminal, int c)
{
	(void)c;
	(void)terminal;
	quit(terminal);
	return (1);
}
