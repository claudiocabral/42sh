/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autocompletion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 14:07:05 by jblazy            #+#    #+#             */
/*   Updated: 2018/05/18 14:07:07 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

char	*str_to_cursor(t_prompt **list)
{
	unsigned int	len;
	unsigned int	i;
	t_prompt		*tmp;
	char			*str;

	len = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp->cursor)
			break ;
		if (!tmp->next && tmp->next_list)
		{
			tmp = tmp->next_list;
			*list = tmp;
			len = 0;
		}
		else
			tmp = tmp->next;
		len++;
	}
	while (tmp && !ft_is_whitespace(tmp->c))
	{
		len++;
		tmp = tmp->next;
	}
	if (!(str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_bzero(str, len + 1);
	i = 0;
	while (*list && i < len)
	{
		if (!(*list)->insertion)
			str[i] = (*list)->c;
		i++;
		if (!(*list)->next && (*list)->next_list)
			*list = (*list)->next_list;
		else
			*list = (*list)->next;
	}
	return (str);
}

void	add_complete(t_prompt **list, char *to_add)
{
	unsigned int	i;

	i = 0;
	while (to_add && to_add[i])
	{
		add_elem(list, create_elem(to_add[i]));
		i++;
	}
	if (to_add)
		ft_strdel(&to_add);
}

void	auto_completion(t_prompt **list)
{
	char		*line;
	t_prompt	*begin_list;

	begin_list = *list;
	line = str_to_cursor(list);
	add_complete(list, auto_complete(line));
	ft_strdel(&line);
	*list = begin_list;
}
