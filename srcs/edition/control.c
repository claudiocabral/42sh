/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 11:26:42 by jblazy            #+#    #+#             */
/*   Updated: 2018/03/15 11:27:02 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

t_prompt	**get_address_list(t_prompt **list, char address)
{
	static t_prompt	**ref;

	if (address)
		ref = list;
	if (address == 2)
		ref = NULL;
	return (ref);
}

void		control_d(t_prompt **list)
{
	display_prompt(*list, 0, 1);
	write(1, "\n", 1);
	free_list(list);
	exit_shell(g_sh);
}

void		control_l(t_prompt **list)
{
	tputs(tgetstr("cl", NULL), 1, &ft_putc);
	display_prompt(*list, 1, 1);
}

void		control_k(t_prompt **list)
{
	t_prompt	*tmp;
	char		delete;

	delete = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp->cursor && !delete)
			delete = 1;
		if (delete)
			delete_delete(list);
		tmp = tmp->next;
	}
}

void		control_u(t_prompt **list)
{
	t_prompt		*tmp;
	unsigned int	i;

	tmp = *list;
	i = 0;
	while (tmp && !tmp->cursor)
	{
		i++;
		tmp = tmp->next;
	}
	while (i-- > 0)
		delete_backspace(list);
}

void		control_w(t_prompt **list)
{
	t_prompt		*tmp;
	unsigned int	i;

	tmp = *list;
	i = 0;
	while (tmp && !tmp->cursor)
	{
		// if (is_skipable(tmp->c))
		if (!is_skipable(tmp->c) && tmp->next && tmp->next->cursor == 0 && is_skipable(tmp->next->c))
			i = 0;
		else
			i++;
		tmp = tmp->next;
	}
	// if (tmp->insertion)
	// 	i++;
	ft_printf("I = %d\n", i);
	while (i-- > 0)
		delete_backspace(list);
}
