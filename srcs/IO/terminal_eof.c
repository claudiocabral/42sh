/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:32:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/23 16:19:15 by ccabral          ###   ########.fr       */
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
	(void)terminal;
	terminal_eol(terminal, 0);
	terminal_insert(terminal, '\n');
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	int			ret;

	ret = 0;
	if (terminal->input_mode == QUOTE_INPUT
			|| terminal->input_mode == BACKSLASH_INPUT)
		return (terminal_insert_newline(terminal));
	else if (terminal->input_mode == HEREDOC_INPUT)
		return (0);
	else if (terminal->input_mode != HEREDOC_INPUT)
		ret = collect_heredocs(terminal);
	terminal_eol(terminal, 0);
	write(STDIN_FILENO, &c, 1);
	return (ret);
}
