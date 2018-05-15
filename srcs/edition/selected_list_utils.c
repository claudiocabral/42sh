/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selected_list_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:14:13 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/14 14:14:22 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

char		*listcpy_tostr(t_prompt *list, unsigned int len)
{
	char	*str;

	if (!(str = ft_strnew(len)))
		return (NULL);
	len = 0;
	while (list)
	{
		if (list->selected && !list->insertion)
			str[len++] = list->c;
		if (!list->next && list->next_list)
			list = list->next_list;
		else if (!list->next && !list->next_list)
			break ;
		else
			list = list->next;
	}
	return (str);
}

char		*selectedlist_to_str(t_prompt *list)
{
	unsigned int	len;
	t_prompt		*tmp;

	len = 0;
	tmp = list;
	while (tmp)
	{
		if (tmp->selected)
			len++;
		if (!tmp->next && tmp->next_list)
			tmp = tmp->next_list;
		else if (!tmp->next && !tmp->next_list)
			break ;
		else
			tmp = tmp->next;
	}
	return (listcpy_tostr(list, len));
}

t_prompt	*selectedstr_to_list(char *str)
{
	t_prompt		*list;
	int				i;

	list = NULL;
	i = -1;
	while (str[i + 1])
	{
		if (!list)
			list = create_elem(str[ft_strlen(str) - 1]);
		else
			add_elem(&list, create_elem(str[i]));
		i++;
	}
	return (list);
}

void		remove_selection(t_prompt *list, t_sh *sh)
{
	ft_strdel(&sh->copy_str);
	list = get_first_list(list);
	while (list)
	{
		if (list->selected)
			list->selected = 0;
		else if (!list->next && list->next_list)
			list = list->next_list;
		else if (!list->next && !list->next_list)
			break ;
		else
			list = list->next;
	}
}
