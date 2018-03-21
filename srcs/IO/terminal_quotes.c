/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 14:11:40 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 14:16:37 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int		terminal_quotes(t_terminal *terminal, int c)
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
