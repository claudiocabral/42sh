/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:25:22 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/13 05:28:32 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

t_prompt			*init_list(void)
{
	t_prompt		*list;

	if (!(list = create_elem(' ')))
		return (0);
	list->cursor = 1;
	list->prompt_type = STANDARD;
	list->insertion = 1;
	return (list);
}

t_prompt			*create_elem(char c)
{
	t_prompt		*new;

	if (!(new = (t_prompt *)malloc(sizeof(t_prompt))))
		return (NULL);
	new->c = c;
	new->cs = 0;
	new->cursor = 0;
	new->insertion = 0;
	new->selected = 0;
	new->previous = NULL;
	new->next = NULL;
	new->previous_list = NULL;
	new->next_list = NULL;
	return (new);
}

void				add_elem(t_prompt **list, t_prompt *new)
{
	t_prompt		*ptr_list;

	ptr_list = *list;
	while (ptr_list->next && !ptr_list->cursor)
		ptr_list = ptr_list->next;
	new->prompt_type = ptr_list->prompt_type;
	if (ptr_list->previous)
	{
		ptr_list->previous->next = new;
		new->previous = ptr_list->previous;
	}
	else
		*list = new;
	ptr_list->previous = new;
	new->next = ptr_list;
	copy_info_elem(new->next, new);
	if ((*list)->previous_list && (*list)->previous_list->next_list
		!= get_first_elem(new))
		list_set_link(new, new->previous_list, "next");
	if ((*list)->next_list && (*list)->next_list->previous_list
		!= get_first_elem(new))
		list_set_link(new, new->next_list, "previous");
}

void				add_nl(t_prompt *list)
{
	t_prompt	*nl;
	t_prompt	*tmp;

	nl = create_elem(RETURN);
	tmp = get_last_elem(list);
	tmp->next = nl;
	nl->previous = tmp;
	nl->previous_list = tmp->previous_list;
	nl->next_list = tmp->next_list;
}

void				expand_line(t_prompt **list)
{
	t_prompt	*expand;

	remove_cursor(*list);
	expand = init_list();
	if ((expand->prompt_type = is_quote_close(get_first_list(*list))) != -1 ||
		check_heredoc(get_first_list(*list)))
	{
		if (expand->prompt_type == -1)
			expand->prompt_type = HEREDOC;
		add_nl(get_last_list(*list));
	}
	else
	{
		if (get_last_elem(*list)->previous)
			get_last_elem(*list)->previous->cs = 36;
		expand->prompt_type = MULTI_LINE;
	}
	list_set_link(expand, get_last_list(*list), "next");
	*list = expand;
}
