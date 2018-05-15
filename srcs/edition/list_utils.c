/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 11:04:16 by jblazy            #+#    #+#             */
/*   Updated: 2018/02/28 15:00:03 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void				copy_info_elem(t_prompt *src, t_prompt *dst)
{
	dst->previous_list = src->previous_list;
	dst->next_list = src->next_list;
}

void				link_elem(t_prompt *previous, t_prompt *next)
{
	if (previous)
		previous->next_list = get_first_elem(next);
	if (next)
		next->previous_list = get_first_elem(previous);
}

/*
**	si l'option est "previous", alors on appliquera sur toute la *list que le
**	nouveau previous_list == link_address; meme principe avec l'option "next".
*/

void				list_set_link(t_prompt *link_address,
						t_prompt *list, char *previous_or_next)
{
	t_prompt		*tmp;
	t_prompt		*info;

	if (!ft_strcmp(previous_or_next, "previous"))
		link_elem(link_address, list);
	else if (!ft_strcmp(previous_or_next, "next"))
		link_elem(list, link_address);
	tmp = get_first_elem(list);
	info = list;
	while (tmp)
	{
		if (info != tmp)
			copy_info_elem(info, tmp);
		tmp = tmp->next;
	}
}

t_prompt			*str_to_list(char *str)
{
	t_prompt		*list;
	unsigned int	i;

	i = 0;
	list = init_list();
	while (str[i])
	{
		if (str[i] == RETURN)
		{
			add_elem(&list, create_elem(' '));
			get_last_elem(list)->previous->insertion = 1;
		}
		add_elem(&list, create_elem(str[i]));
		i++;
	}
	return (list);
}

void				list_apply_type(t_prompt *list, char type)
{
	while (list)
	{
		list->prompt_type = type;
		list = list->next;
	}
}
