/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reducers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <iomonad@riseup.net>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 16:52:06 by ctrouill          #+#    #+#             */
/*   Updated: 2018/06/10 14:15:55 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <stdlib.h>
#include <stdio.h>
#include <globbing.h>

static t_bool	need_reduce(const char *origin)
{
	return (ft_strcmp(origin, "*") == 0
			|| ft_strcmp(origin, "**") == 0
			|| ft_strcmp(origin, "*.") == 0);
}

static void		popify(t_list **prev, t_list **aref)
{
	(*prev)->next = (*aref)->next;
	free((*aref)->content);
	free(*aref);
	*aref = *prev;
}

static void		k(t_list **prev, t_list **aref)
{
	*prev = *aref;
	*aref = (*aref)->next;
}

void			dot_reduce(t_list **head, const char *origin, t_list *aref)
{
	t_list		*prev;

	aref = *head;
	prev = aref;
	if (*head != NULL && need_reduce(origin))
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
					popify(&prev, &aref);
			}
			else
				k(&prev, &aref);
		}
	}
}
