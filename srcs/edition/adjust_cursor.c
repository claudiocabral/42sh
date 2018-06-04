/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adjust_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/20 14:33:00 by jblazy            #+#    #+#             */
/*   Updated: 2018/02/28 14:50:48 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

unsigned int		up_accordingto_len(t_prompt *list)
{
	int				len;
	unsigned int	nb_up;
	struct winsize	w;

	nb_up = 0;
	len = prompt_len(list);
	ioctl(0, TIOCGWINSZ, &w);
	w.ws_col = (w.ws_col <= 0) ? 1 : w.ws_col;
	while (list->next)
	{
		if (list->c == RETURN)
		{
			nb_up += (len - 1) / w.ws_col;
			len = 0;
		}
		else
			len++;
		list = list->next;
	}
	nb_up += (len / w.ws_col);
	return (nb_up);
}

int					get_height_prompt(t_prompt *list)
{
	unsigned int	height;
	t_prompt		*tmp;

	tmp = get_first_list(list);
	height = 0;
	while (tmp)
	{
		height += up_accordingto_len(tmp);
		height += list_nb_return(tmp);
		if (tmp && get_last_elem(tmp)->c != RETURN && tmp->next_list)
			height++;
		tmp = tmp->next_list;
	}
	return (height);
}

void				adjust_cursor(t_prompt *list)
{
	int nb_up;

	nb_up = get_height_prompt(list);
	while (nb_up > 0)
	{
		tputs(tgetstr("up", NULL), 1, &ft_putc);
		nb_up--;
	}
}

void				remove_cursor(t_prompt *list)
{
	t_prompt		*tmp;

	tmp = get_first_elem(list);
	while (tmp && !tmp->cursor)
		tmp = tmp->next;
	if (tmp)
		tmp->cursor = 0;
}
