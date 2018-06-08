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

unsigned int	get_len(t_prompt **tmp, unsigned int len, unsigned int begin)
{
	len = 0;
	while ((*tmp) && !(*tmp)->cursor)
	{
		if (!(*tmp)->next && (*tmp)->next_list)
		{
			(*tmp) = (*tmp)->next_list;
			len = 0;
		}
		else
			(*tmp) = (*tmp)->next;
		len++;
	}
	while (*tmp && !ft_is_whitespace((*tmp)->c))
	{
		len++;
		(*tmp) = (*tmp)->next;
	}
	begin = len;
	while (*tmp && (*tmp)->previous && !ft_is_whitespace((*tmp)->previous->c))
	{
		begin--;
		(*tmp) = (*tmp)->previous;
	}
	return (len - begin);
}

char			*str_to_cursor(t_prompt *tmp)
{
	unsigned int	len;
	unsigned int	i;
	char			*str;

	len = get_len(&tmp, 0, 0);
	if (!(str = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (tmp && i < len)
	{
		if (!tmp->insertion)
			str[i++] = tmp->c;
		tmp = tmp->next;
	}
	return (str);
}

t_prompt		*get_cursor(t_prompt *tmp)
{
	while (tmp->next && !tmp->cursor)
		tmp = tmp->next;
	return (tmp);
}

void			add_complete(t_prompt **list, char *to_add)
{
	unsigned int	i;
	t_prompt		*tmp;

	i = 0;
	while ((tmp = get_cursor(*list)) && tmp->c != ' ')
		move_right(list);
	while (to_add && to_add[i])
	{
		add_elem(list, create_elem(to_add[i]));
		i++;
	}
	if (to_add)
		ft_strdel(&to_add);
}

void			auto_completion(t_prompt **list)
{
	char		*line;
	t_prompt	*begin_list;

	begin_list = *list;
	line = str_to_cursor(*list);
	add_complete(list, auto_complete(line));
	ft_strdel(&line);
	*list = begin_list;
}
