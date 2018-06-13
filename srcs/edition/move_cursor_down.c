/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_cursor_down.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:20:33 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 13:20:41 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

static t_prompt	*goto_next_line(t_prompt *list, int index, int col)
{
	while (list->next)
	{
		if (list->c == RETURN)
			return (list->next);
		else if (index == col)
			return (list);
		index++;
		list = list->next;
	}
	return (list);
}

static void		finish_moving(t_prompt **list, t_prompt *next_line,
		t_prompt *tmp, unsigned int index)
{
	tmp->cursor = 0;
	if (!next_line->next && (*list)->next_list)
	{
		index -= prompt_len((*list)->next_list);
		tmp = (*list)->next_list;
		*list = (*list)->next_list;
	}
	else
		tmp = next_line;
	while (tmp->next && tmp->next->c != RETURN && index-- > 0)
		tmp = tmp->next;
	tmp->cursor = 1;
}

void			move_down(t_prompt **list)
{
	t_prompt			*tmp;
	t_prompt			*next_line;
	struct winsize		w;
	unsigned int		index;

	tmp = *list;
	ioctl(0, TIOCGWINSZ, &w);
	index = prompt_len(*list);
	while (tmp->next && !tmp->cursor)
	{
		if (index == w.ws_col || tmp->c == RETURN)
			index = tmp->c == RETURN ? -1 : 0;
		index++;
		tmp = tmp->next;
	}
	next_line = goto_next_line(tmp, index, w.ws_col);
	if (!next_line->next)
		return ;
	finish_moving(list, next_line, tmp, index);
}
