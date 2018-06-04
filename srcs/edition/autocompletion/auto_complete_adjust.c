/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_adjust.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 11:19:55 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/03 23:59:55 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void			add_possibilty(t_prompt **list, t_autocompl *array,
					t_infocompl *info)
{
	int	i;

	i = 0;
	while (i < info->size)
	{
		if (array[i].cursor == 1)
		{
			add_complete(list, ft_strdup(array[i].str + ft_strlen(info->str)));
			free_autocompletion(g_sh);
			return ;
		}
		i++;
	}
}

void			input_autocompletion(char *input, t_prompt **list,
					t_infocompl *info)
{
	if (input[0] == TAB && input[1] == 0 && !info)
		auto_completion(list);
	else if ((input[0] == TAB && input[1] == 0) || !ft_strncmp(input, DOWN, 4))
		move_down_autocompl(info->array, info);
	else if (!ft_strncmp(input, UP, 4))
		move_up_autocompl(info->array, info);
	else if (!ft_strncmp(input, RIGHT, 4))
		move_right_autocompl(info->array, info);
	else if (!ft_strncmp(input, LEFT, 4))
		move_left_autocompl(info->array, info);
	else if (input[0] == RETURN && input[1] == 0)
		add_possibilty(list, info->array, info);
}

void			choose_possibility(t_array *array, char *str)
{
	t_autocompl	*possibilities;
	t_infocompl	*info;
	int			size;
	int			i;
	char		**it;

	size = array_size(array);
	if (!(info = (t_infocompl *)malloc(sizeof(t_infocompl))))
		return ;
	if (!(possibilities = (t_autocompl *)malloc(sizeof(t_autocompl) * size)))
		return ;
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
	info->str ? free(info->str) : 0;
	info->str = str;
	g_sh->completion = info;
}
