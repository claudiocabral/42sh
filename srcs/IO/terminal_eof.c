/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_eof.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 14:32:28 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 20:03:01 by ccabral          ###   ########.fr       */
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

int		terminal_eof(t_terminal *terminal, int c)
{
	int			ret;
	t_string	*str;

	ret = 0;
	if (terminal->input_mode == QUOTE_INPUT)
	{
		++terminal->line_number;
		terminal_insert(terminal, c);
		if (!(str = string_create(terminal->line->size)))
			return (1);
		//string_copy(str, terminal->line);
		//terminal_draw(terminal, str);
		string_free(str);
		return (1);
	}
	else if (terminal->input_mode == HEREDOC_INPUT)
		return (0);
	else if (terminal->input_mode != HEREDOC_INPUT)
		ret = collect_heredocs(terminal);
	write(STDIN_FILENO, &c, 1);
	return (ret);
}
