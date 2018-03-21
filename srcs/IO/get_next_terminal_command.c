/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_terminal_command.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 18:53:37 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/21 17:34:18 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>
#include <ft_string.h>

int		get_next_terminal_command(t_terminal *terminal, t_string *str)
{
	int	ret;

	ret = terminal_get_line(terminal, terminal->history_fd, 1);
	if (ret == -1)
		return (ret);
	string_copy(str, terminal->line);
	string_clear(terminal->line);
	terminal->cursor = 0;
	terminal->line_number = 0;
	return (!ret);
}
