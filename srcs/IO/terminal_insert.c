/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:54:21 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/20 16:37:44 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <io.h>
#include <ft_printf.h>

int		terminal_insert(t_terminal *terminal, int c)
{
	terminal_command(INSERT, 1);
	write(STDIN_FILENO, &c, 1);
	if (!string_insert(terminal->line, c,
				terminal->cursor - terminal->prompt_size))
		return (-1);
	terminal->cursor++;
	return (1);
}

int		terminal_insert_string(t_terminal *terminal, char *str)
{
	int	i;

	terminal_command(INSERT, 1);
	ft_dprintf(STDIN_FILENO, "%s", str);
	i = 0;
	while (str[i])
	{
		if (!string_insert(terminal->line, str[i],
					terminal->cursor - terminal->prompt_size))
			return (-1);
		++(terminal->cursor);
		++i;
	}
	return (1);
}

int		terminal_eof(t_terminal *terminal, int c)
{
	if (terminal->line->buffer[terminal->cursor - terminal->prompt_size]
			== '\\')
		return (terminal_insert(terminal, c));
	write(STDIN_FILENO, &c, 1);
	return (0);
}

int		terminal_noop(t_terminal *terminal, int c)
{
	(void)terminal;
	(void)c;
	return (1);
}
