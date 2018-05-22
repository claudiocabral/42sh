/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:23:50 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/05 17:23:53 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

unsigned int		return_str_len(t_prompt *list)
{
	unsigned int	len;

	len = 0;
	list = get_first_list(list);
	while (list)
	{
		if (list->next && !(list->c == BACKSLASH && !list->next->next))
			len++;
		list = list->next;
		if (list && !list->next)
			list = list->next_list;
	}
	return (len);
}

char				*list_to_str(t_prompt **list)
{
	t_prompt		*tmp;
	unsigned int	i;
	char			*str;

	tmp = get_first_list(*list);
	i = return_str_len(*list);
	if (!(str = ft_strnew(i)))
		return (NULL);
	i = 0;
	while (tmp)
	{
		if (!((tmp->c == BACKSLASH && !tmp->next->next)
			|| (tmp->insertion && !tmp->next_list)))
		{
			if (tmp->next && tmp->next->c == RETURN)
				str[i] = RETURN;
			if (!(tmp->insertion && tmp->next && tmp->next->c == RETURN) &&
				tmp->c != RETURN)
				str[i] = tmp->c;
				i++;
		}
		tmp = tmp->next;
		if (tmp && !tmp->next)
			tmp = tmp->next_list;
	}
	return (str);
}
