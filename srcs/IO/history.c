/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:52:09 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/21 18:53:18 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <io.h>

int						history_previous(t_terminal *terminal, int c)
{
	(void)c;
	terminal_bol(terminal, 0);
	terminal_delete_until_eol(terminal, 0);
	string_copy(terminal->line,
			(t_string *)ring_buffer_previous(terminal->history));
	terminal_command(INSERT, terminal->line->size);
	write(STDIN_FILENO, terminal->line->buffer, terminal->line->size);
	terminal->cursor += terminal->line->size;
	return (1);
}

int						history_next(t_terminal *terminal, int c)
{
	t_string	*next;

	(void)c;
	if ((next = (t_string *)ring_buffer_next(terminal->history))
			== terminal->history->next)
		return (1);
	terminal_bol(terminal, 0);
	terminal_delete_until_eol(terminal, 0);
	string_copy(terminal->line, next);
	terminal_command(INSERT, terminal->line->size);
	write(STDIN_FILENO, terminal->line->buffer, terminal->line->size);
	terminal->cursor += terminal->line->size;
	return (1);
}

int	open_history(t_terminal *terminal)
{
	if ((terminal->history_fd = open("~/.21sh_history", O_APPEND)) == -1)
	{
		ft_dprintf(2, "21sh: failed to open history file\n");
		return (0);
	}
	return (1);
}

int	append_history(t_terminal *terminal)
{
	write(terminal->history_fd, terminal->line->buffer, terminal->line->size);
	return (1);
}

int	load_history(t_terminal *terminal)
{
	t_string	*str;
	int			ret;

	ring_buffer_clean(terminal->history, (t_freef) & string_free_content);
	while (1)
	{
		str = ring_buffer_push_empty(terminal->history);
		if ((ret = get_next_terminal_command(terminal->history_fd, str)) == -1)
			return (0);
		else if (ret == 0)
			return (1);
	}
}
