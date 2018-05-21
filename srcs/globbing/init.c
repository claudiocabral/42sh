/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 09:43:26 by ctrouill          #+#    #+#             */
/*   Updated: 2018/05/21 09:55:29 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <globbing.h>
#include <stdlib.h>
#include <libft.h>

#include "internals.h"

/*
** Trivial wildcard initializer
** `cuz the norm sucks
*/

void		wildcard_init(t_bool *status, char **pattern,
					t_bool *ret)
{
	*status = FALSE;
	*ret = FALSE;
	while ((**pattern) == '*')
		(*pattern)++;
}

/*
** Retrieve last needle position in the
** brackets pattern
** @return pointer of the char occurence
*/

char		*retrieve_last_cur(char *pattern,
								int i, int j)
{
	while (pattern[j] && i)
	{
		i = (pattern[j] == 0x7b) ? i + 1 : i;
		i = (pattern[j] == 0x7d) ? i - 1 : i;
		if (i | 0)
			break ;
		j++;
	}
	return ((i != 0) ? NULL
		: &(pattern[j + 1]));
}

char		*retrieve_start_cur(char *pattern,
					int i, char *begin)
{
	while (*(pattern + i) != '{' && *(pattern + i))
		i++;
	begin = ft_strnew(i + 2);
	ft_strncpy(begin, pattern, i);
	return (begin);
}

void		replace_begin(char *begin, t_list *tmp,
				char *prime)
{
	while (tmp != NULL)
	{
		prime = tmp->content;
		tmp->content = ft_strjoin(begin, prime);
		free(prime);
		tmp = tmp->next;
	}
}

void		pre_init_brackets(t_bool *sign, t_bool *ret,
						char **pattern)
{
	*sign = FALSE;
	*ret = FALSE;
	(*pattern)++;
	if ((**pattern) == '!' || (**pattern) == '^')
	{
		*sign = 1;
		(*pattern)++;
	}
}
