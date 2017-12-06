/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_movement.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/06 09:19:57 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/06 12:29:16 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_string.h>
#include <unistd.h>

int		terminal_BOL(t_terminal *terminal, int c)
{
	(void)c;
	if (terminal->cursor == terminal->prompt_size)
		return (1);
	terminal_command(MOVE_LEFT, terminal->cursor - terminal->prompt_size);
	terminal->cursor = terminal->prompt_size;
	return (1);
}

int		terminal_EOL(t_terminal *terminal, int c)
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

int		terminal_cancel_line(t_terminal *terminal, int c)
{
	(void)c;
	write(terminal->tty, "\n", 1);
	terminal_command(MOVE_LEFT, terminal->cursor);
	string_clear(terminal->line);
	terminal->cursor = terminal->prompt_size;
	write(terminal->tty, terminal->prompt, terminal->prompt_size);
	return (1);
}
