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

void 			move_down_autocompl(t_autocompl *possibilities, t_info *info)
{
	int		i;

	i = 0;
	while (i < info->size)
	{
		if (possibilities[i].cursor == 1)
		{
			if (i + info->elem_col < info->size)
				possibilities[i + info->elem_col].cursor = 1;
			else
				possibilities[0].cursor = 1;
			possibilities[i].cursor = 0;
			return ;
		}
		i++;
	}
	possibilities[0].cursor = 1;
}

void			choose_action(t_autocompl *possibilities, t_info *info)
{
	char		input[4];
	// char		*str;
	t_prompt	**list;

	list = get_address_list(NULL, 0);
	ft_memset(&input, 0, 4);
	while (read(0, &input, 4))
	{
		// if (input[0] == RETURN)
		// {
		// 	if ((str = input_return(sh, &list)))
		// 		return (str);
		// }
		// ft_putnbr(input[0]);
		// ft_putchar('\n');
		// ft_putnbr(input[1]);
		// ft_putchar('\n');
		// ft_putnbr(input[2]);
		// ft_putchar('\n');
		// ft_putnbr(input[3]);
		// ft_putchar('\n');
		if (input[0] == TAB && input[1] == 0)
			move_down_autocompl(possibilities, info);
		// else if (input_possibilities_move(&input[0], &list) == 1)
		// 	;
		// else
		// 	input_possibilities_else(&input[0], &list, sh);
		get_address_list(list, 1);
		display_possibilities(possibilities, info);
		ft_memset(&input, 0, 4);
	}
}

char			*choose_possibility(t_array *array, char *str)
{
	t_autocompl	*possibilities;
	t_info		info;
	int			size;
	int			i;
	char		**it;

	size = array_size(array);
	if (!(possibilities = (t_autocompl *)malloc(sizeof(t_autocompl) * size)))
		return (NULL);
	ft_printf("SIZE = %d\n", size);
	i = 0;
	it = (char **)array->begin;
	while (it != array->end)
	{
		ft_printf("IT = %s\n", *it);
		possibilities[i].str = ft_strdup(*it);
		possibilities[i].cursor = 0;
		it++;
		i++;
	}
	info.size = size;
	sort_possibilites(possibilities, &info);
	ft_putchar('\n');
	display_possibilities(possibilities, &info);
	choose_action(possibilities, &info);
	// tputs(tgetstr("up", NULL), 1, &ft_putc);
	(void)str;
	return (NULL);
}
// int			choose_possibility(t_array *array, char *str,
// 		t_terminal *terminal)
// {
// 	char	**it;
// 	char	*candidate;
// 	int		size;
// 	int		max_size;
//
// 	ZERO_IF_FAIL((it = (char **)array->begin) != array->end);
// 	candidate = *it;
// 	max_size = ft_strlen(candidate);
// 	while (it != array->end)
// 	{
// 		size = 0;
// 		while (size < max_size && (*it)[size] == candidate[size])
// 			++size;
// 		max_size = size;
// 		++it;
// 	}
// 	if ((size_t)size == ft_strlen(str))
// 		return (print_options(array, terminal));
// 	max_size = candidate[size];
// 	candidate[size] = 0;
// 	if (str)
// 		terminal_insert_string(terminal,
// 				candidate + ft_strlen(str));
// 	candidate[size] = (char)max_size;
// 	return (1);
// }
