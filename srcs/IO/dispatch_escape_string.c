/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch_escape_string.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 15:47:14 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/21 15:51:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <io.h>

int	dispatch_escape_string(t_terminal *terminal, char *c)
{
	if (ft_strequ(c, "\eb"))
		return (terminal_previous_word(terminal, (int)c[0]));
	else if (ft_strequ(c, "\ef"))
		return (terminal_next_word(terminal, (int)c[0]));
	return (1);
}
