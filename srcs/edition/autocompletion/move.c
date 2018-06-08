/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblazy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 16:07:26 by jblazy            #+#    #+#             */
/*   Updated: 2018/06/08 16:07:28 by jblazy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void			move_left_autocompl(t_autocompl *possibilities,
					t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			possibilities[i].cursor = 0;
			if (i > info->row - 1)
				possibilities[i - info->row].cursor = 1;
			else if (i == 0)
				possibilities[(info->col - 1) * info->row].cursor = 1;
			else if (i - 1 + (info->col - 1) * info->row < info->size)
				possibilities[i - 1 + (info->col - 1) * info->row].cursor = 1;
			else
				possibilities[i - 1 + (info->col - 2) * info->row].cursor = 1;
			return ;
		}
		i++;
	}
}

void			move_right_autocompl(t_autocompl *possibilities,
					t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			possibilities[i].cursor = 0;
			if (i + info->row < info->size)
				possibilities[i + info->row].cursor = 1;
			else if (i % info->row == info->row - 1)
				possibilities[i % info->row].cursor = 1;
			else
				possibilities[i % info->row + 1].cursor = 1;
			return ;
		}
		i++;
	}
}

void			move_up_autocompl(t_autocompl *possibilities, t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			possibilities[i].cursor = 0;
			if (i - 1 > -1)
				possibilities[i - 1].cursor = 1;
			else
				possibilities[info->size - 1].cursor = 1;
			return ;
		}
		i++;
	}
}

void			move_down_autocompl(t_autocompl *possibilities,
					t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			possibilities[i].cursor = 0;
			if (i + 1 < info->size)
				possibilities[i + 1].cursor = 1;
			else
				possibilities[0].cursor = 1;
			return ;
		}
		i++;
	}
	possibilities[0].cursor = 1;
}
