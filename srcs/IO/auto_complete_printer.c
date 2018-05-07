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

#include <unistd.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <array.h>
#include <io.h>

int			get_biggest_column(t_array *array)
{
	char	**it;
	int		max;

	it = (char **)array->begin;
	max = 0;
	while (it != array->end)
	{
		max = ft_max(max, ft_strlen(*it));
		++it;
	}
	return (max);
}

void		print_columns_helper(int nbr_columns, int nbr_rows,
									int column_size, t_array *array)
{
	char	**it;
	int		i;
	int		j;
	int		size;

	(void)nbr_columns;
	it = array->begin;
	size = array_size(array);
	i = 0;
	while (i < nbr_rows)
	{
		j = 0;
		while (i + (j * nbr_rows) < size)
		{
			ft_dprintf(0, "%*s%c",
				i + (j + 1) * nbr_rows >= size ?
				-1 * (long)ft_strlen(*(it + i + j * nbr_rows))
				: -1 * column_size,
				*(it + i + j * nbr_rows),
				i + (j + 1) * nbr_rows >= size ? '\n' : '\t');
			++j;
		}
		++i;
	}
}

static int	print_columns(t_array *array)
{
	int	column_size;
	int	nbr_columns;
	int	nbr_rows;
	int	size;

	size = array_size(array);
	column_size = get_biggest_column(array);
	nbr_columns = ft_max(1, get_terminal_width() / ((column_size + 8) / 8 * 8));
	nbr_rows = size / nbr_columns + ((size % nbr_columns) != 0);
	print_columns_helper(nbr_columns, nbr_rows, column_size, array);
	return (nbr_rows);
}

void		auto_complete_push(t_array *array, char *base, char *candidate)
{
	size_t	ret;

	if (!base || !candidate)
		return ;
	if ((!*base || (ret = ft_strnequ(base, candidate, ft_strlen(base))))
			&& !array_find(array, &candidate, (t_cmpf) & ft_strcmp_wrapper))
		ret = (size_t)array_push_back(array, &candidate);
	else
	{
		free(candidate);
		return ;
	}
	if (!ret)
		free(candidate);
}

int			print_options(t_array *array, t_terminal *terminal)
{
	int		nbr_lines;

	write(0, "\n", 1);
	terminal_command(CLEAR_BOTTOM, 0);
	nbr_lines = print_columns(array) + 1;
	adjust_terminal(terminal, nbr_lines);
	return (1);
}
