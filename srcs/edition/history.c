/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ctrouill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 14:39:00 by ctrouill          #+#    #+#             */
/*   Updated: 2018/02/28 14:59:17 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

/*
** Print History
** @return nil
*/

void					history(t_histo_list *history)
{
	t_histo_list		*tmp;
	unsigned int		index;

	index = 0;
	tmp = history;
	while (tmp->next)
		tmp = tmp->next;
	while (tmp)
	{
		ft_putnbr(tmp->index);
		ft_putstr("  ");
		ft_putstr(tmp->command);
		ft_putchar('\n');
		tmp = tmp->previous;
		index++;
	}
}

/*
** Reset historic cursor
** @return nil
*/

void					history_reset_cursor(t_histo_list *history)
{
	t_histo_list		*tmp;

	tmp = history;
	while (tmp)
	{
		tmp->cursor = 0;
		tmp = tmp->next;
	}
}

/*
** Add new history elem
** @return nil
*/

t_histo_list			*history_new_elem(char *command)
{
	t_histo_list		*new;

	if (!(new = (t_histo_list *)malloc(sizeof(t_histo_list))))
		return (NULL);
	new->command = ft_strdup(command);
	new->index = 0;
	new->cursor = 0;
	new->previous = NULL;
	new->next = NULL;
	return (new);
}

/*
** Add command to the history
** @return nil
*/

void					history_add_command(t_histo_list **history,
											char *command)
{
	t_histo_list		*new;

	if (!(new = history_new_elem(command)))
		return ;
	if (*history)
	{
		new->index = (*history)->index + 1;
		new->next = *history;
		(*history)->previous = new;
	}
	*history = new;
	history_reset_cursor(*history);
}
