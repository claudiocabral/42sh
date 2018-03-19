/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_kill_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:24:47 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:25:01 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>

int						terminal_delete_until_eol(t_terminal *terminal, int c)
{
	int		current_position;

	current_position = terminal->cursor;
	terminal_eol(terminal, c);
	while (terminal->cursor > current_position)
		terminal_delete(terminal, c);
	return (1);
}

int						terminal_kill_line(t_terminal *terminal, int c)
{
	(void)c;
	terminal_eol(terminal, 0);
	write(0, "\n", 1);
	string_clear(terminal->line);
	print_prompt(terminal);
	terminal->cursor = 0;
	return (1);
}
