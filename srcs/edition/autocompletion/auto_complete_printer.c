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

void			calc_start_end(t_autocompl *possibilities, t_infocompl *info)
{
	int		h;
	int		height_prompt;
	int		row_cursor;

	height_prompt = get_height_prompt(*(get_address_list(NULL, 0))) + 1;
	h = info->height - height_prompt;
	row_cursor = 0;
	while (row_cursor < info->size)
	{
		if (possibilities[row_cursor].cursor)
			break ;
		row_cursor++;
	}
	row_cursor = row_cursor == info->size ? 0 : row_cursor % info->row + 1;
	if (row_cursor > h)
	{
		info->display_start = row_cursor - h;
		info->display_end = row_cursor;
	}
	else
	{
		info->display_start = 0;
		info->display_end = info->row < info->height ?
			info->row : info->height - height_prompt;
	}
}

void			display_col(t_autocompl *possibilities, t_infocompl *info,
					int row, int *first_nl)
{
	int pos;
	int col_indent[2];

	col_indent[0] = 0;
	while (col_indent[0] < info->col)
	{
		pos = col_indent[0] * info->row + row;
		if (pos < info->row && pos)
			(*first_nl)++;
		if (pos < info->row && pos && (!info->display_start ||
			(info->display_start > 0 && *first_nl > 1)))
			ft_putchar('\n');
		if (pos < info->size)
		{
			if (possibilities[pos].cursor)
				ft_putstr(REVERSE_VIDEO);
			ft_putstr(possibilities[pos].str);
			if (possibilities[pos].cursor)
				ft_putstr(RESET);
			col_indent[1] = info->max_size - ft_strlen(possibilities[pos].str);
			while (col_indent[0] + 1 < info->col && col_indent[1]-- >= 0)
				ft_putchar(' ');
		}
		col_indent[0]++;
	}
}

void			display_it(t_autocompl *possibilities, t_infocompl *info)
{
	int		row;
	int		first_nl;

	row = info->display_start;
	first_nl = 0;
	while (row < info->display_end && row < info->row)
	{
		display_col(possibilities, info, row, &first_nl);
		row++;
	}
}

void			prepare_display(t_autocompl *possibilities, t_infocompl *info)
{
	struct winsize		w;
	int					i;

	ioctl(0, TIOCGWINSZ, &w);
	info->width = w.ws_col > 0 ? w.ws_col : 1;
	info->height = w.ws_row > 0 ? w.ws_row : 1;
	info->max_size = 0;
	i = 0;
	while (i < info->size)
	{
		if (ft_strlen(possibilities[i].str) + 3 > info->max_size)
			info->max_size = ft_strlen(possibilities[i].str) + 3;
		i++;
	}
	info->col = info->width / info->max_size == 0 ?
		1 : info->width / info->max_size;
	info->row = info->size / info->col;
	if (info->size % info->col > 0)
		info->row++;
	calc_start_end(possibilities, info);
}

void			display_completion(t_infocompl *info)
{
	int		tmp;

	ft_putchar('\n');
	prepare_display(info->array, info);
	display_it(info->array, info);
	tmp = info->display_end - info->display_start;
	while (tmp-- > 0)
		tputs(tgetstr("up", NULL), 1, &ft_putc);
}
