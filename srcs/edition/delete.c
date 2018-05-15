/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:06:14 by jblazy            #+#    #+#             */
/*   Updated: 2018/02/28 14:51:50 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void			check_if_insert(t_prompt **list, t_prompt *check_elem)
{
	if (check_elem->insertion && check_elem->next &&
		check_elem->next->c == RETURN)
		delete_current_elem(list, check_elem->next);
	else if (check_elem->c == RETURN && check_elem->previous
		&& check_elem->previous->insertion)
		delete_current_elem(list, check_elem->previous);
}

/*
** Delete char using backspace
** @return nil
*/

void			delete_backspace(t_prompt **list)
{
	t_prompt	*ptr_list;

	ptr_list = *list;
	while (ptr_list->next && !ptr_list->cursor)
		ptr_list = ptr_list->next;
	if (ptr_list->previous)
	{
		if (ptr_list->previous->c == RETURN && ptr_list->previous->previous)
			delete_current_elem(list, ptr_list->previous->previous);
		delete_current_elem(list, ptr_list->previous);
	}
}

/*
**	Delete the address of to_del and connect his previous to his next and
**	vice-versa. This function is used by delete_delete and by cut. Sometimes
**	list == NULL when it is used by cut.
**	@return void
*/

void			delete_current_elem(t_prompt **list, t_prompt *to_del)
{
	if (to_del->next)
	{
		to_del->next->previous = to_del->previous;
		if (to_del->previous)
			to_del->previous->next = to_del->next;
		else
		{
			if (list)
				*list = to_del->next;
			if (to_del->next->previous_list)
				list_set_link(to_del->next, to_del->next->previous_list,
					"next");
			if (to_del->next->next_list)
				list_set_link(to_del->next, to_del->next->next_list,
					"previous");
		}
		if (to_del->cursor)
			to_del->next->cursor = 1;
		free_elem(&to_del);
	}
}

/*
** Delete char using delete
** @return nil
*/

void			delete_delete(t_prompt **list)
{
	t_prompt	*ptr_list;

	ptr_list = *list;
	while (ptr_list->next && !ptr_list->cursor)
		ptr_list = ptr_list->next;
	if (ptr_list->next && !(ptr_list->insertion && !ptr_list->next->next))
	{
		if (ptr_list->insertion && ptr_list->next->c == RETURN)
			delete_current_elem(list, ptr_list->next);
		delete_current_elem(list, ptr_list);
	}
}
