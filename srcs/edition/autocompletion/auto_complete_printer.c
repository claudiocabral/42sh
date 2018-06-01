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

void 			display_it(t_autocompl *possibilities, t_infocompl *info)
{
	int		col;
	int		row;
	int		position;
	int		indent;

	row = 0;
	while (row < info->row)
	{
		col = 0;
		while (col < info->col)
		{
			position = col * info->row + row;
			if (position < info->row && position)
				ft_putchar('\n');
			if (position < info->size)
			{
				if (possibilities[position].cursor)
				ft_putstr(REVERSE_VIDEO);
				ft_putstr(possibilities[position].str);
				if (possibilities[position].cursor)
				ft_putstr(RESET);
				indent = info->max_size - ft_strlen(possibilities[position].str);
				while (col + 1 < info->col && indent-- >= 0)
				ft_putchar(' ');
			}
			col++;
		}
		row++;
	}
}

void			prepare_display(t_autocompl *possibilities, t_infocompl *info)
{
	struct winsize		w;
	int					i;

	ioctl(0, TIOCGWINSZ, &w);
	info->width = w.ws_col != 0 ? w.ws_col : 1;
	info->max_size = 0;
	i = 0;
	while (i < info->size)
	{
		if (ft_strlen(possibilities[i].str) + 3 > info->max_size)
			info->max_size = ft_strlen(possibilities[i].str) + 3;
		i++;
	}
	info->col = info->width / info->max_size == 0 ? info->max_size : 1;
	info->row = info->size / info->col;
	if (info->size % info->col > 0)
		info->row++;
}

void			display_completion(t_infocompl *info)
{
	int		tmp;

	ft_putchar('\n');
	prepare_display(info->array, info);
	display_it(info->array, info);
	tmp = info->row;
	while (tmp--)
		tputs(tgetstr("up", NULL), 1, &ft_putc);
}
