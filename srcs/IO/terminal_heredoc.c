/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:17:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 17:32:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <libft.h>
#include <ft_printf.h>
#include <slice.h>
#include <io.h>

char		*skip_white_spaces(char const *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		++str;
	return ((char *)str);
}

static int	heredoc_loop(t_terminal *terminal, t_slice eof)
{
	char	*current_line;

	while (1)
	{
		if (terminal->fd == STDIN_FILENO && terminal->buffer_size != 1)
			ft_dprintf(STDIN_FILENO, "heredoc> ", 0);
		if (terminal_get_line(terminal,
					terminal->fd, terminal->buffer_size) == 0)
		{
			if (!(current_line = ft_strrchr(terminal->line->buffer, '\n')))
				return (0);
			if (ft_strnequ(skip_white_spaces(current_line + 1),
						eof.ptr, eof.size))
				break ;
			terminal_insert(terminal, '\n');
		}
	}
	return (1);
}

static int	terminal_heredoc(t_terminal *terminal, t_slice eof)
{
	if (check_complete_heredoc(eof))
		return (0);
	terminal_eol(terminal, 0);
	terminal_insert(terminal, '\n');
	heredoc_loop(terminal, eof);
	return (0);
}

t_slice		get_next_heredoc(char const **line)
{
	int		i;
	t_slice	eof;

	i = 0;
	while (**line)
	{
		if ((*line)[0] == '<' && (*line)[1] == '<')
		{
			*line = skip_white_spaces(*line + 2);
			while ((*line)[i] && !ft_is_whitespace((*line)[i])
					&& (*line)[i] != '\n')
				++i;
			eof = make_slice(*line, i);
			*line += i;
			return (eof);
		}
		++(*line);
	}
	return (error_slice());
}

int			collect_heredocs(t_terminal *terminal)
{
	t_slice		eof;
	char const	*line;
	char const	*end;

	line = terminal->line->buffer;
	end = line + terminal->line->size;
	terminal->input_mode = HEREDOC_INPUT;
	while ((eof = get_next_heredoc(&line)).ptr)
		terminal_heredoc(terminal, eof);
	terminal->input_mode = NORMAL_INPUT;
	return (0);
}
