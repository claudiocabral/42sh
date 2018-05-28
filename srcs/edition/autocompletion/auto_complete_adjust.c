/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_adjust.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:19:55 by ccabral           #+#    #+#             */
/*   Updated: 2018/02/02 13:06:30 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void 			move_right_autocompl(t_autocompl *possibilities, t_infocompl *info)
{
	int		i;

	i = 0;
	ft_printf("ROW = %d ## COL = %d\n", info->row, info->col);
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			ft_printf("I = %d\n", i);
			if (i + info->row < info->size)
				possibilities[i + info->row].cursor = 1;
			ft_printf("I = %d\n", i + info->row);
			// else
			// 	possibilities[i % info->col].cursor = 1;
			possibilities[i].cursor = 0;
			return ;
		}
		i++;
	}
}

void 			move_up_autocompl(t_autocompl *possibilities, t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			if (i - 1 > -1)
				possibilities[i - 1].cursor = 1;
			else
				possibilities[info->size - 1].cursor = 1;
			possibilities[i].cursor = 0;
			return ;
		}
		i++;
	}
}

void 			move_down_autocompl(t_autocompl *possibilities, t_infocompl *info)
{
	int		i;

	i = 0;
	ft_printf("ROW = %d ## COL = %d\n", info->row, info->col);
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			if (i + 1 < info->size)
				possibilities[i + 1].cursor = 1;
			else
				possibilities[0].cursor = 1;
			possibilities[i].cursor = 0;
			return ;
		}
		i++;
	}
	possibilities[0].cursor = 1;
}

void			input_autocompletion(char *input, t_prompt **list, t_infocompl *info)
{
	if (input[0] == TAB && input[1] == 0 && !info)
		auto_completion(list);
	else if ((input[0] == TAB && input[1] == 0) || !ft_strncmp(input, DOWN, 4))
		move_down_autocompl(info->array, info);
	else if (!ft_strncmp(input, UP, 4))
		move_up_autocompl(info->array, info);
	else if (!ft_strncmp(input, RIGHT, 4))
		move_right_autocompl(info->array, info);
	(void)list;
}

char			*choose_possibility(t_array *array, char *str)
{
	t_autocompl	*possibilities;
	t_infocompl	*info;
	int			size;
	int			i;
	char		**it;

	size = array_size(array);
	if (!(info = (t_infocompl *)malloc(sizeof(t_infocompl))))
		return (NULL);
	if (!(possibilities = (t_autocompl *)malloc(sizeof(t_autocompl) * size)))
		return (NULL);
	i = 0;
	it = (char **)array->begin;
	while (it != array->end)
	{
		possibilities[i].str = ft_strdup(*it);
		possibilities[i].cursor = 0;
		it++;
		i++;
	}
	info->size = size;
	sort_possibilites(possibilities, info);
	info->array = possibilities;
	g_sh->completion = info;
	(void)str;
	return (NULL);
}
