/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_LR.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/08 14:34:26 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/08 14:34:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void	move_left(t_prompt **list)
{
	t_prompt	*tmp;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (tmp->previous)
	{
		tmp->cursor = 0;
		if (tmp->previous->c == RETURN && tmp->previous->previous)
			tmp->previous->previous->cursor = 1;
		else if (tmp->previous->c != RETURN)
			tmp->previous->cursor = 1;
	}
	else if (tmp->previous_list)
	{
		tmp->cursor = 0;
		(*list) = tmp->previous_list;
		tmp = get_last_elem(*list);
		if (tmp->c == RETURN)
			tmp->previous->cursor = 1;
		else
			tmp->cursor = 1;
	}
}

void	move_right(t_prompt **list)
{
	t_prompt	*tmp;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (tmp->next)
	{
		tmp->cursor = 0;
		if (tmp->next->c == RETURN && tmp->next->next)
			tmp->next->next->cursor = 1;
		else if (tmp->next->c == RETURN)
		{
			(*list) = tmp->next_list;
			(*list)->cursor = 1;
		}
		else
			tmp->next->cursor = 1;
	}
	else if (tmp->next_list)
	{
		tmp->cursor = 0;
		(*list) = tmp->next_list;
		(*list)->cursor = 1;
	}
}

void	word_left(t_prompt **list)
{
	t_prompt	*tmp;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (!tmp->previous && !tmp->previous_list)
		return ;
	tmp->cursor = 0;
	if (tmp->previous && !is_skipable(tmp->c) && is_skipable(tmp->previous->c))
		tmp = tmp->previous;
	while (tmp)
	{
		if (!tmp->previous && tmp->previous_list)
		{
			tmp = get_last_elem((*list)->previous_list);
			*list = (*list)->previous_list;
		}
		else if (!tmp->previous || !is_skipable(tmp->c))
			break ;
		tmp = tmp->previous;
	}
	while (tmp->previous && !is_skipable(tmp->previous->c))
		tmp = tmp->previous;
	tmp->cursor = 1;
}

void	word_right(t_prompt **list)
{
	t_prompt	*tmp;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	if (!tmp->next && !tmp->next_list)
		return ;
	tmp->cursor = 0;
	if (tmp->next && !is_skipable(tmp->c) && is_skipable(tmp->next->c))
		tmp = tmp->next;
	while (tmp)
	{
		if (!tmp->next && tmp->next_list)
		{
			tmp = tmp->next_list;
			*list = tmp;
		}
		else if (!tmp->next || !is_skipable(tmp->next->c))
			break ;
		tmp = tmp->next;
	}
	while (tmp->next && !is_skipable(tmp->next->c))
		tmp = tmp->next;
	tmp->cursor = 1;
}
