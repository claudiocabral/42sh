/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   braks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 09:49:32 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/13 10:52:46 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>

#include "internals.h"

/*
** Compute brackets matching internal runners
** For error handling
** @return boolean/ Exec[Status]
*/

t_bool			compute_match_bracket(t_helper *glob, char *str,
						char *pattern, t_list **results)
{
	t_bool	sign;
	t_bool	status;

	pre_init_brackets(&sign, &status, &pattern);
	while (*pattern != ']' && *pattern)
	{
		if (!(status))
		{
			if (*(pattern + 1) == '-' && *(pattern + MAGIC_OFFSET) != ']')
			{
				status = (*pattern <= *str
					&& *(pattern + MAGIC_OFFSET) >= *str) != sign;
				pattern += MAGIC_OFFSET;
			}
			status = ((*pattern == '[' && *(pattern + 1) == ':')) ?
				(init_brackets_offset(&pattern, *str, 1, 1) != (int)sign)
					: status;
			status = (((*pattern == *str) != sign)) ? 1 : status;
		}
		pattern++;
	}
	pattern += *pattern != 0;
	return (status && pattern_dispatcher(glob, str + 1, pattern, results));
}

/*
** Execute brackets runner that will check format
** and context. When invalid context occur, just
** alloc pseudo buffer an return null
** @return Pseudo buffer | Nil
*/

char			*exec_brackets(char **format, int *err,
					char *internal, int i)
{
	char		*str;

	str = *format;
	while (brackets_valid_fmt(**format))
	{
		if (*(*format) == 0x7b)
			retrieve_brackets_occur(format, 0);
		else
		{
			i++;
			(*format)++;
		}
	}
	if (have_valid_context(*err, **format)
		== FALSE)
	{
		internal = ft_strnew(i + MAGIC_OFFSET);
		ft_strncpy(internal, str, i);
	}
	return (internal);
}
