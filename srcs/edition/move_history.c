/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:54:26 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 13:54:32 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
** Move down in history
** @return nil
*/

void					history_down(t_prompt **list, t_histo_list *history)
{
	t_histo_list		*tmp;

	tmp = history;
	while (tmp && tmp->next && tmp->next->cursor)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->cursor = 0;
		free_list(list);
		if (tmp->previous)
			*list = str_to_list(tmp->previous->command);
		else
			*list = init_list();
	}
}

/*
** Move up in history
** @return nil
*/

void					history_up(t_prompt **list, t_histo_list *history)
{
	t_histo_list		*tmp;

	tmp = history;
	while (tmp && tmp->cursor)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->cursor = 1;
		free_list(list);
		*list = str_to_list(tmp->command);
	}
}
