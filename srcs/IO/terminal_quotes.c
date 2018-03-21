/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:11:40 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 17:38:39 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int	terminal_quotes(t_terminal *terminal, int c)
{
	if (terminal->input_mode != QUOTE_INPUT)
	{
		terminal->input_mode = QUOTE_INPUT;
		terminal->quote = (char)c;
		terminal_insert(terminal, c);
		return (1);
	}
	if (c == terminal->quote)
	{
		terminal->input_mode = NORMAL_INPUT;
		terminal->quote = 0;
		terminal_insert(terminal, c);
		return (1);
	}
	return (terminal_insert(terminal, c));
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	terminal_delete_quote(t_terminal *terminal)
{
	if (terminal->input_mode == QUOTE_INPUT)
	{
		if (terminal->quote == terminal->line->buffer[terminal->cursor - 1])
		{
			terminal->input_mode = NORMAL_INPUT;
			terminal->quote = 0;
		}
	}
	else if (is_quote(terminal->line->buffer[terminal->cursor - 1]))
	{
		terminal->input_mode = QUOTE_INPUT;
		terminal->quote = terminal->line->buffer[terminal->cursor - 1];
	}
	return (1);
}
