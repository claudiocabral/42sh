/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 15:17:29 by jblazy            #+#    #+#             */
/*   Updated: 2018/02/28 14:38:46 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void			free_list(t_prompt **list)
{
	t_prompt	*tmp;

	*list = get_first_list(*list);
	while (*list)
	{
		tmp = *list;
		if (!(*list)->next && (*list)->next_list)
			*list = (*list)->next_list;
		else
			*list = (*list)->next;
		free_elem(&tmp);
	}
	list = NULL;
}

void			free_elem(t_prompt **elem)
{
	free(*elem);
	*elem = NULL;
	elem = NULL;
}
