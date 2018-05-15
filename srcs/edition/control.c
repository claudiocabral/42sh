/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:26:42 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/15 11:27:02 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

t_prompt	**get_address_list(t_prompt **list, char address)
{
	static t_prompt	**ref;

	if (address)
		ref = list;
	if (address == 2)
		ref = NULL;
	return (ref);
}

void		control_d(t_prompt **list)
{
	display_prompt(*list, 0, 1);
	write(1, "\n", 1);
	free_list(list);
	exit_shell(g_sh);
}

void		control_l(t_prompt **list)
{
	tputs(tgetstr("cl", NULL), 1, &ft_putc);
	display_prompt(*list, 1, 1);
}
