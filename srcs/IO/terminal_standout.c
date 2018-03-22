/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_standout.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:09:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 14:10:45 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int		terminal_rewrite(t_terminal *terminal)
{
	if (terminal->cursor == 0 || terminal->cursor == (long)terminal->line->size)
		return (1);
	write(STDIN_FILENO, terminal->line->buffer + terminal->cursor, 1);
	terminal_command(MOVE_LEFT, 1);
	return (1);
}

void	terminal_move_rewrite(t_terminal *terminal, int movement)
{
	if (terminal->cursor + movement < 0
			|| terminal->cursor + movement >= (long)terminal->line->size)
		return ;
	if (movement < 0)
	{
		terminal_rewrite(terminal);
		terminal_move_left(terminal, 0);
	}
	else
	{
		terminal_rewrite(terminal);
		terminal_move_right(terminal, 0);
	}
}

void	restore_terminal_position(t_terminal *terminal, int position)
{
	terminal_command(NO_STANDOUT, 0);
	terminal_rewrite(terminal);
	while (terminal->cursor < position)
	{
		terminal_move_right(terminal, 0);
		terminal_rewrite(terminal);
	}
	while (terminal->cursor > position)
	{
		terminal_move_left(terminal, 0);
		terminal_rewrite(terminal);
	}
}

void	terminal_standout(t_terminal *terminal, int initial_pos, int movement)
{
	if ((movement > 0 && terminal->cursor + movement - initial_pos == 1)
			|| (movement < 0
				&& terminal->cursor + movement - initial_pos == -1))
		terminal_command(STANDOUT, 0);
	else if (initial_pos < terminal->cursor)
	{
		if (movement > 0)
			terminal_command(STANDOUT, 0);
		else
			terminal_command(NO_STANDOUT, 0);
	}
	else
	{
		if (movement < 0)
			terminal_command(STANDOUT, 0);
		else
			terminal_command(NO_STANDOUT, 0);
	}
	terminal_move_rewrite(terminal, movement);
}
