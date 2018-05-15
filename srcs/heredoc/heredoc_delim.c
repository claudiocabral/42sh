/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_delim.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:42:42 by jblazy            #+#    #+#             */
/*   Updated: 2018/04/13 16:42:44 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	Set the variable g_sh->heredoc_delim.
**	@return the end of the delim;
*/

t_prompt	*set_delim(t_prompt *list)
{
	unsigned int	len;
	t_prompt		*tmp;
	char			*delim;

	len = 0;
	tmp = list;
	while (tmp && !is_operand(tmp->c) && !is_skipable(tmp->c))
	{
		len++;
		tmp = tmp->next ? tmp->next : tmp->next_list;
	}
	if (!(delim = ft_strnew(len)))
		exit(-1);
	len = 0;
	tmp = list;
	while (tmp && !is_operand(tmp->c) && !is_skipable(tmp->c))
	{
		if (!tmp->insertion)
			delim[len] = tmp->c;
		len++;
		tmp = (tmp->next) ? tmp->next : tmp->next_list;
	}
	g_sh->heredoc_delim = delim;
	return (tmp);
}

/*
**	@return a list's pointer, if there is one occurence (which delimits the end
**	of the heredoc) of the heredoc delimiter in the list.
**	@return NULL else.
*/

t_prompt	*cmp_list_delim(t_prompt *list)
{
	int			i;

	i = 0;
	while (list)
	{
		if (i == 0 && (!list->previous || list->previous->c == '\n')
			&& list->c == g_sh->heredoc_delim[i])
			i++;
		else if (i > 0 && list->c == g_sh->heredoc_delim[i])
			i++;
		else
			i = 0;
		list = list->next ? list->next : list->next_list;
		if (!g_sh->heredoc_delim[i] && list->insertion)
			return (list);
	}
	return (NULL);
}

/*
**	find the begin of the delimiter, if there is only space, it returns NULL.
*/

t_prompt	*find_delim(t_prompt *list)
{
	list = list->next->next;
	while (list && is_skipable(list->c) && !is_operand(list->c))
		list = list->next;
	return (list);
}

/*
**	@return the length of the delimiter.
*/

int			list_delim_len(t_prompt *delim)
{
	int		len;

	len = 0;
	while (delim->next && !is_skipable(delim->c) && !is_operand(delim->c))
	{
		delim = delim->next;
		len++;
	}
	return (len);
}
