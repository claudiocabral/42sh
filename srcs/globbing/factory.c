/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   factory.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <ctrouill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/18 18:47:22 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 13:24:46 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "internals.h"

/*
** Generate a new string from a prebuilt
** glob structure and return the expansion
** of the string.
*/

char		*build_result(t_list *results, t_list *tmp,
				int len, char *final)
{
	tmp = results;
	while (tmp != NULL)
	{
		len += tmp->content_size;
		tmp = tmp->next;
	}
	if (len != 0)
		final = ft_strnew(len);
	len = 0;
	while (results != NULL)
	{
		tmp = results->next;
		strcpy(final + len, (char*)results->content);
		len = len + results->content_size;
		if (tmp != NULL)
			*(final + len - 1) = ' ';
		free(results->content);
		free(results);
		results = tmp;
	}
	return (final);
}

/*
** Second part of the generator, see below.
*/

static int	you_norminette_sucks(const char *pattern, t_helper gi,
					t_list **res, int p)
{
	t_list		*ps;
	t_list		*next;

	ps = ft_lstnew(pattern, ft_strlen(pattern) + 1);
	if (compile_glob_brace(ps, NULL, NULL, NULL) == -1)
		p = -1;
	while (ps != NULL)
	{
		next = ps->next;
		if (!p && !ft_strchr(ps->content, '{'))
			call_dirwalker(gi, ps->content, res, NULL);
		free(ps->content);
		free(ps);
		ps = next;
	}
	return (!p);
}

/*
** Principal globbing runner, find
** and match patterns to fill the current
** glob structure
*/

int			compute_globbing(const char *pattern,
					t_glob *gl)
{
	t_helper			g;

	if ((prepare_gbuff(&g)) && prepare_glob(gl))
		return (you_norminette_sucks(pattern, g, &gl->final_list, 0));
	return (FALSE);
}
