/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_up.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:25:36 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 13:25:39 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

static t_prompt	*goto_previous_line(t_prompt *list, int index)
{
	while (index-- > 0 && list->previous)
		list = list->previous;
	return (list);
}

t_prompt		*get_last_line(t_prompt *list, int col)
{
	int			index;
	t_prompt	*last_line;

	index = prompt_len(list);
	while (list->next)
	{
		if (index == col || list->c == RETURN)
			index = list->c == RETURN ? -1 : 0;
		index++;
		list = list->next;
	}
	last_line = goto_previous_line(list, index);
	return (last_line);
}

static void		finish_moving(t_prompt **list, t_prompt *previous_line,
		t_prompt *tmp, int index)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	tmp->cursor = 0;
	if (previous_line)
		tmp = previous_line;
	else
	{
		tmp = get_last_line((*list)->previous_list, w.ws_col);
		*list = (*list)->previous_list;
	}
	if (tmp == *list)
		index -= prompt_len(*list);
	while (tmp->next && tmp->next->c != RETURN && index-- > 0)
		tmp = tmp->next;
	tmp->cursor = 1;
}

void			move_up(t_prompt **list)
{
	t_prompt		*tmp;
	t_prompt		*previous_line;
	struct winsize	w;
	int				index;

	tmp = *list;
	previous_line = NULL;
	ioctl(0, TIOCGWINSZ, &w);
	index = prompt_len(*list);
	while (tmp->next && !tmp->cursor)
	{
		if (index == w.ws_col || tmp->c == RETURN)
		{
			previous_line = goto_previous_line(tmp, index);
			index = (tmp->c == RETURN) ? -1 : 0;
		}
		index++;
		tmp = tmp->next;
	}
	if (!previous_line)
		return ;
	finish_moving(list, previous_line, tmp, index);
}
