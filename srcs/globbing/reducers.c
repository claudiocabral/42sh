/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:52:06 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/09 19:04:37 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <globbing.h>

void		dot_reduce(t_list **head, const char *origin, t_list *aref)
{
	t_list	*prev;

	aref = *head;
	prev = aref;
	if (*head != NULL && (ft_strcmp(origin, "*") == 0
						  || ft_strcmp(origin, "**") == 0))
	{
		while (aref != NULL)
		{
			if (ft_strnequ(aref->content, DOOM, 3))
			{
				if (aref == *head)
				{
					*head = aref->next;
					free(aref->content);
					free(aref);
					aref = *head;
				}
				else
				{
					prev->next = aref->next;
					free(aref->content);
					free(aref);
					aref = prev;
				}
			}
			else
			{
				prev = aref;
				aref = aref->next;
			}
		}
	}
}
