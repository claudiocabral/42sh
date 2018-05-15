/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 09:20:15 by ctrouill          #+#    #+#             */
/*   Updated: 2018/04/18 17:42:42 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
** Interrupt (ANSI)
** Program interrupt. (ctrl-c)
** @states prompt reset
*/

void			sigint_callback(void)
{
	t_prompt	**list;

	list = get_address_list(NULL, 0);
	if (list)
	{
		display_prompt(*list, 0, 0);
		ft_putchar('\n');
		free_list(list);
		*list = init_list();
		display_prompt(*list, 1, 1);
	}
}
