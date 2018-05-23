/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_printer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:05:38 by ccabral           #+#    #+#             */
/*   Updated: 2018/05/07 14:35:14 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void 			display_it(t_autocompl *possibilities, t_info *info)
{
	int		i;
	int		indent;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor)
			ft_putstr(REVERSE_VIDEO);
		ft_putstr(possibilities[i].str);
		if (possibilities[i].cursor)
			ft_putstr(RESET);
		if ((i + 1) % info->elem_col == 0)
			ft_putchar('\n');
		else
		{
			indent = info->max_size - ft_strlen(possibilities[i].str);
			while (indent-- >= 0)
				ft_putchar(' ');
		}
		i++;
	}
	ft_putchar('\n');
}

void			prepare_display(t_autocompl *possibilities, t_info *info)
{
	struct winsize		w;
	int					i;

	ioctl(0, TIOCGWINSZ, &w);
	info->width = w.ws_col;
	info->max_size = 0;
	i = 0;
	while (i < info->size)
	{
		if (ft_strlen(possibilities[i].str) + 3 > info->max_size)
			info->max_size = ft_strlen(possibilities[i].str) + 3;
		i++;
	}
	info->elem_col = info->width / info->max_size;
}

void			display_possibilities(t_autocompl *possibilities, t_info *info)
{
	prepare_display(possibilities, info);
	display_it(possibilities, info);
	// tputs(tgetstr("up", NULL), 1, &ft_putc);
}
