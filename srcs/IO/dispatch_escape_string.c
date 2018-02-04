/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_escape_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:47:14 by ccabral           #+#    #+#             */
/*   Updated: 2018/02/02 14:54:29 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int	terminal_escape(t_terminal *terminal, int c)
{
	(void)c;
	terminal->input_mode = ESCAPE_INPUT;
	return (1);
}

int	dispatch_escape_string(t_terminal *terminal, char *c)
{
	if (ft_strequ(c, "\eb"))
		return (terminal_previous_word(terminal, (int)c[0]));
	else if (ft_strequ(c, "\ef"))
		return (terminal_next_word(terminal, (int)c[0]));
	return (1);
}
