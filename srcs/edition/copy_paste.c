/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/09 14:09:47 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/09 14:09:57 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void		copy(t_prompt **list, char input, t_sh *sh)
{
	t_prompt	*tmp;
	char		*selected_str;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
	{
		tmp = tmp->next;
		if (!tmp->next && tmp->next_list)
			tmp = tmp->next_list;
	}
	if (!tmp->insertion)
	{
		tmp->selected = (!tmp->selected) ? 1 : 0;
		selected_str = selectedlist_to_str(get_first_list(*list));
		if (sh->copy_str)
			ft_strdel(&sh->copy_str);
		sh->copy_str = selected_str;
	}
	if (input == ALT_D)
		move_right(list);
	else
		move_left(list);
}

void		paste(t_prompt **list, t_sh *sh)
{
	t_prompt	*tmp;
	t_prompt	*selected_list;

	tmp = *list;
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	selected_list = selectedstr_to_list(sh->copy_str);
	list_apply_type(selected_list, (*list)->prompt_type);
	if (tmp->previous)
	{
		tmp->previous->next = selected_list;
		selected_list->previous = tmp->previous;
	}
	else
		*list = selected_list;
	tmp->previous = get_last_elem(selected_list);
	get_last_elem(selected_list)->next = tmp;
	copy_info_elem(tmp, selected_list);
	if (selected_list->previous_list)
		list_set_link(selected_list, selected_list->previous_list, "next");
	if (selected_list->next_list)
		list_set_link(selected_list, selected_list->next_list, "previous");
}

void		cut_delete(t_prompt **list, t_prompt *tmp, t_prompt *to_del)
{
	if (*list == get_first_elem(tmp))
	{
		if (to_del->insertion && to_del->next && to_del->next->c == RETURN)
			delete_current_elem(list, to_del->next);
		delete_current_elem(list, to_del);
	}
	else
	{
		if (to_del->insertion && to_del->next && to_del->next->c == RETURN)
			delete_current_elem(NULL, to_del->next);
		delete_current_elem(NULL, to_del);
	}
}

void		cut(t_prompt **list)
{
	t_prompt	*tmp;
	t_prompt	*to_del;

	tmp = get_first_list(*list);
	to_del = NULL;
	while (tmp)
	{
		if (tmp->selected)
			to_del = tmp;
		if (!tmp->next && tmp->next_list)
			tmp = tmp->next_list;
		else if (!tmp->next && !tmp->next_list)
			break ;
		else
			tmp = tmp->next;
		if (to_del)
		{
			cut_delete(list, tmp, to_del);
			to_del = NULL;
		}
	}
}
