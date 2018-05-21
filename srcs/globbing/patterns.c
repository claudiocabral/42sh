/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 19:44:06 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 13:25:12 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>

#include "internals.h"

/*
** Retrieve a list of
*/

static inline int	retrieve_patterns_list(t_list **patterns,
								char *pattern)
{
	char			*occur;
	char			*end;
	int				err;
	int				ret;
	char			*join;

	ret = 0;
	err = -1;
	if (!(end = retrieve_last_cur(pattern, 1, 0)))
		return (0);
	while ((occur = exec_brackets(&pattern, &err, NULL, 0))
			&& err && *pattern)
	{
		join = ft_strjoin(occur, end);
		ft_lstprepend(patterns, ft_xlstnew(join, ft_strlen(join) + 1));
		free(occur);
		ret++;
		pattern++;
	}
	free(occur);
	return ((!err) ? -1 : ret);
}

/*
** Match brace cross reference
** and verify correct formation
** @return Check status
*/

int					compile_glob_brace(t_list *first, char *begin,
						t_list *tmp, char *prime)
{
	int				n;

	while (first != NULL)
	{
		prime = first->content;
		begin = retrieve_start_cur(prime, 0, NULL);
		while (*prime && *prime != '{')
			prime++;
		if (*prime == '{' &&
			(n = retrieve_patterns_list(&tmp, prime + 1)) > 0)
		{
			ft_lstprepend(&first, tmp);
			replace_begin(begin, tmp, NULL);
		}
		first = first->next;
		free(begin);
	}
	return ((n == -1) ? n : 0);
}

/*
** Trivial function dispacther depending
** on the pattern passed on parameters
** and the relsult.
** @return exec_status
*/

t_bool				pattern_dispatcher(t_helper *g, char *s,
						char *pattern, t_list **results)
{
	if (*s == '\0' && *pattern == '\0')
		return (TRUE);
	else if (*pattern == '*')
		return (compute_match_wildcard(g, s, pattern, results));
	else if (!*s || !*pattern)
		return (FALSE);
	else if (*pattern == '/')
		call_dirwalker(*g, pattern + 1, results, NULL);
	else if (*pattern == '\\' && *(pattern + 1) == *s)
		return (pattern_dispatcher(g, s + 1, pattern + MAGIC_OFFSET, results));
	else if (*s == *pattern)
		return (pattern_dispatcher(g, s + 1, pattern + 1, results));
	else if (*pattern == '?')
		return (pattern_dispatcher(g, s + 1, pattern + 1, results));
	else if (*pattern == '[')
		return (compute_match_bracket(g, s, pattern, results));
	return (FALSE);
}
