/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 16:33:55 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/20 16:33:57 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
**	@return the pointer of list + iteration.
*/

t_prompt	*forward_list(t_prompt *list, size_t iteration)
{
	while (list && iteration)
	{
		list = list->next;
		iteration--;
	}
	return (list);
}

/*
**	@return a pointer of the beginning of the heredoc-block.
*/

t_prompt	*to_begin_heredoc(t_prompt *list)
{
	while (list && list->next)
	{
		if (list->c == '\n')
			return (list);
		list = list->next;
	}
	return (!list ? list : list->next_list);
}

/*
**	The variable heredoc_ref, refers to our position in the line where
**	heredoc(s) where invocated. If the position is at the end of the line,
**	we return.
**	@return 1 if there is an open heredoc.
**	@return 0 if there is no heredoc or a close heredoc.
*/

int			check_heredoc(t_prompt *list)
{
	t_prompt	*heredoc;

	heredoc = NULL;
	while (list && list->next)
	{
		if (list->c == '<' && list->next && list->next->c == '<')
		{
			if (!(list = find_delim(list)))
				break ;
			if (!g_sh->heredoc_delim && list)
				list = set_delim(list);
			if (!heredoc)
				heredoc = to_begin_heredoc(list);
			heredoc = cmp_list_delim(heredoc);
			ft_strdel(&(g_sh->heredoc_delim));
			if (!heredoc)
				return (1);
		}
		else
		{
			list = list->next;
			list = (!list->next && list->next_list) ? list->next_list : list;
		}
	}
	return (0);
}
