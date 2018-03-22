/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:32:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 20:23:03 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <ft_printf.h>
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

int		terminal_insert_newline(t_terminal *terminal)
{
	int	width;

	++terminal->line_number;
	width = get_terminal_width();
	terminal_command(CLEAR_BOTTOM, 0);
	terminal_insert(terminal, '\n');
	write(STDIN_FILENO, terminal->line->buffer + terminal->cursor,
			terminal->line->size - terminal->cursor);
	terminal_command(MOVE_LEFT, terminal->line->size - terminal->cursor);
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	int			ret;

	ret = 0;
	if (terminal->input_mode == QUOTE_INPUT)
		return (terminal_insert_newline(terminal));
	else if (terminal->input_mode == HEREDOC_INPUT)
		return (0);
	else if (terminal->input_mode != HEREDOC_INPUT)
		ret = collect_heredocs(terminal);
	write(STDIN_FILENO, &c, 1);
	return (ret);
}
