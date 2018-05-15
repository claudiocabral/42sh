/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:45:43 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 13:45:51 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

t_prompt			*get_first_list(t_prompt *list)
{
	t_prompt		*tmp;

	tmp = list;
	while (tmp->previous_list)
		tmp = tmp->previous_list;
	return (tmp);
}

t_prompt			*get_last_list(t_prompt *list)
{
	t_prompt		*tmp;

	tmp = list;
	while (tmp->next_list)
		tmp = tmp->next_list;
	return (tmp);
}

t_prompt			*get_first_elem(t_prompt *list)
{
	t_prompt		*tmp;

	tmp = list;
	while (tmp && tmp->previous)
		tmp = tmp->previous;
	return (tmp);
}

t_prompt			*get_last_elem(t_prompt *list)
{
	t_prompt		*tmp;

	tmp = list;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}
