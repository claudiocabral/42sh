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

// int			nbr_characters(char const *str)
// {
// 	int	nbr;
//
// 	nbr = 0;
// 	while (1)
// 	{
// 		while (is_middle_of_unicode(*str))
// 			++str;
// 		if (!*str)
// 			break ;
// 		++str;
// 		++nbr;
// 	}
// 	return (nbr);
// }

void 			move_down_autocompl(t_autocompl *possibilities, t_infocompl *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			if (i + info->col < info->size)
				possibilities[i + info->col].cursor = 1;
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
	else if (input[0] == TAB && input[1] == 0)
		move_down_autocompl(info->array, info);
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
