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

static void				history_link_list(t_prompt *previous_list,
					t_prompt *next_list, t_prompt **list)
{
	if (next_list)
	{
		list_set_link(next_list, *list, "next");
		list_set_link(*list, (*list)->next_list, "previous");
	}
	if (previous_list)
	{
		list_set_link(previous_list, *list, "previous");
		list_set_link(*list, (*list)->previous_list, "next");
	}
}

/*
** Move down in history
** @return nil
*/

void					history_down(t_prompt **list, t_histo_list *history)
{
	t_histo_list		*tmp;
	t_prompt			*next_list;
	t_prompt			*previous_list;
	char				save_type;

	tmp = history;
	next_list = (*list)->next_list;
	previous_list = (*list)->previous_list;
	while (tmp && tmp->next && tmp->next->cursor)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->cursor = 0;
		save_type = (*list)->prompt_type;
		free_list(list);
		if (tmp->previous)
			*list = str_to_list(tmp->previous->command);
		else
			*list = init_list();
		list_apply_type(*list, save_type);
		history_link_list(previous_list, next_list, list);
	}
}

/*
** Move up in history
** @return nil
*/

void					history_up(t_prompt **list, t_histo_list *history)
{
	t_histo_list		*tmp;
	t_prompt			*next_list;
	t_prompt			*previous_list;
	char				save_type;

	tmp = history;
	next_list = (*list)->next_list;
	previous_list = (*list)->previous_list;
	while (tmp && tmp->cursor)
		tmp = tmp->next;
	if (tmp)
	{
		tmp->cursor = 1;
		save_type = (*list)->prompt_type;
		free_list(list);
		*list = str_to_list(tmp->command);
		list_apply_type(*list, save_type);
		history_link_list(previous_list, next_list, list);
	}
}
