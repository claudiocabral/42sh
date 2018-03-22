/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:52:09 by claudioca         #+#    #+#             */
/*   Updated: 2018/03/22 16:55:19 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <ft_printf.h>
#include <io.h>

int	history_previous(t_terminal *terminal, int c)
{
	(void)c;
	terminal_draw(terminal,
			(t_string *)ring_buffer_previous(terminal->history));
	return (1);
}

int	history_next(t_terminal *terminal, int c)
{
	t_string	*next;

	(void)c;
	if ((next = (t_string *)ring_buffer_next(terminal->history))
			== terminal->history->next)
		return (1);
	terminal_draw(terminal, next);
	return (1);
}

int	history_open(t_terminal *terminal, int mode)
{
	if ((terminal->history_fd = open(".21sh_history", mode,
					S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) == -1)
	{
		ft_dprintf(2, "21sh: failed to open history file\n");
		return (0);
	}
	return (1);
}

int	history_append(t_terminal *terminal)
{
	history_open(terminal, O_RDWR | O_APPEND | O_CREAT);
	write(terminal->history_fd, terminal->line->buffer, terminal->line->size);
	write(terminal->history_fd, "\n", 1);
	close(terminal->history_fd);
	terminal->history_fd = 0;
	return (1);
}

int	history_load(t_terminal *terminal)
{
	t_string	*str;
	int			ret;
	int			tmp;

	tmp = dup(STDIN_FILENO);
	close(STDIN_FILENO);
	if (terminal->history_fd == 0
			&& !history_open(terminal, O_RDONLY | O_CREAT))
		return (0);
	ring_buffer_clean(terminal->history, (t_freef) & string_clear);
	terminal->fd = terminal->history_fd;
	terminal->buffer_size = 1;
	while (1)
	{
		str = ring_buffer_push_empty(terminal->history);
		if ((ret = get_next_terminal_command(terminal, str)) == -1)
			break ;
		else if (ret == 0)
			break ;
	}
	history_cleanup(terminal, tmp);
	return (ret != -1);
}
