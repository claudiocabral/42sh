/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_string.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 17:23:50 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/13 05:30:19 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

unsigned int		return_str_len(t_prompt *list)
{
	unsigned int	len;

	len = 0;
	while (list && list->next)
	{
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
	i = return_str_len(tmp);
	if (!(str = ft_strnew(i + 32)))
		return (NULL);
	ft_bzero(str, 32 + i);
	i = 0;
	while (tmp)
	{
		if (!tmp->insertion && tmp->cs == 0)
			str[i++] = tmp->c;
		if (tmp->c == '\\' && !tmp->next && !tmp->next_list)
			--i;
		if (tmp && !tmp->next)
			tmp = tmp->next_list;
		else
			tmp = tmp->next;
	}
	return (str);
}
