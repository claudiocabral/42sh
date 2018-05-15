/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_BE.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 13:09:44 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/09 13:09:52 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void	move_begin(t_prompt **list)
{
	t_prompt		*tmp;
	struct winsize	w;

	tmp = *list;
	ioctl(0, TIOCGWINSZ, &w);
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (!tmp->previous && !tmp->previous_list)
		return ;
	tmp->cursor = 0;
	if (!tmp->previous)
	{
		tmp = get_last_line(tmp->previous_list, w.ws_col);
		*list = (*list)->previous_list;
	}
	else
	{
		tmp = tmp->previous;
		while (tmp->previous && tmp->previous->c != RETURN)
			tmp = tmp->previous;
	}
	tmp->cursor = 1;
}

void	move_end(t_prompt **list)
{
	t_prompt	*tmp;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (!tmp->next && !tmp->next_list)
		return ;
	tmp->cursor = 0;
	if (!tmp->next || (tmp->next->c == RETURN && !tmp->next->next))
	{
		tmp = tmp->next_list;
		*list = (*list)->next_list;
	}
	else
		tmp = tmp->next;
	while (tmp->next && tmp->next->c != RETURN)
		tmp = tmp->next;
	tmp->cursor = 1;
}
