/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:17:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/19 14:22:35 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <io.h>

char	*skip_white_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		++str;
	return (str);
}

int		heredoc_loop(t_terminal *terminal, char const *condition)
{
	char	*current_line;

	while (1)
	{
		ft_dprintf(STDIN_FILENO, "heredoc> ", 0);
		if (terminal_get_line(terminal) == 0)
		{
			if (!(current_line = ft_strrchr(terminal->line->buffer, '\n')))
				return (0);
			if (ft_strequ(skip_white_spaces(current_line + 1), condition))
			{
				terminal_insert(terminal, '\n');
				break ;
			}
			terminal_insert(terminal, '\n');
		}
	}
	return (1);
}

int		terminal_heredoc(t_terminal *terminal, char *eof)
{
	char	*condition;

	if (eof == terminal->line->buffer || *(eof - 1) != '<'
			|| !eof[1])
	{
		write(STDIN_FILENO, "\n", 1);
		return (0);
	}
	ZERO_IF_FAIL(condition = ft_strdup(skip_white_spaces(eof + 1)));
	terminal_eol(terminal, 0);
	terminal_insert(terminal, '\n');
	terminal->input_mode = HEREDOC_INPUT;
	heredoc_loop(terminal, condition);
	free(condition);
	terminal->input_mode = NORMAL_INPUT;
	return (0);
}
