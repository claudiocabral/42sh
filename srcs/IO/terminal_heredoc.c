/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/18 14:17:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/18 14:42:17 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <io.h>

int	heredoc_loop(t_terminal *terminal, char const *condition)
{
	char	*current_line;

	(void)terminal;
	current_line = terminal->line->buffer + terminal->line->size;
	while (!ft_strequ(current_line, condition))
	{
		return (1);
	}
	return (1);
}

int	terminal_heredoc(t_terminal * terminal, char *eof)
{
	char	*condition;
	if (eof == terminal->line->buffer || *(eof - 1) != '<'
			|| !eof[1])
	{
		write(STDIN_FILENO, "\n", 1);
		return (0);
	}
	ZERO_IF_FAIL(condition = ft_strdup(eof + 1));
	terminal_eol(terminal, 0);
	terminal_insert(terminal, '\n');
	heredoc_loop(terminal, condition);
	free(condition);
	return (0);
}
