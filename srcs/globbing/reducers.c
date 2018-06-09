/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:52:06 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/09 18:35:46 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <globbing.h>

void		dot_reduce(t_list **head, const char *origin, t_list *aref)
{
	aref = *head;

	if (*head != NULL && ft_strcmp(origin, "*") == 0)
	{
		while (aref != NULL)
		{
			if (ft_strnequ(aref->content, DOOM, 3))
			{
				/* TODO: Poping these elements */
				dprintf(2, "\" To pop: %s\"\n", aref->content);
			}
			aref = aref->next;
		}
	}
}
