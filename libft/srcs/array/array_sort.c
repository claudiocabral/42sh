/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:59:31 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/25 12:48:18 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>
#include <libft.h>

void	array_swap(t_array *array, void *a, void *b)
{
	ft_memcpy(array->end, a, array->element_size);
	ft_memcpy(a, b, array->element_size);
	ft_memcpy(b, array->end, array->element_size);
	ft_bzero(array->end, array->element_size);
}

void	*array_partition(t_array *array, void *low, void *high, t_cmpf cmpf)
{
	void	*i;
	void	*j;
	void	*pivot;

	pivot = high;
	j = low;
	i = low - array->element_size;
	while (j < high)
	{
		if (cmpf(j, pivot) < 0)
		{
			i += array->element_size;
			array_swap(array,  i, j);
		}
		j += array->element_size;
	}
	i += array->element_size;
	if (cmpf(high, i) < 0)
		array_swap(array, i, high);
	return (i);
}

void			array_sort_impl(t_array *array, void *low, void *high,
															t_cmpf cmpf)
{
	void	*p;

	if (low < high)
	{
		p = array_partition(array, low, high, cmpf);
		array_sort_impl(array, low, p - array->element_size, cmpf);
		array_sort_impl(array, p + array->element_size, high, cmpf);
	}
}

__attribuet__((always_inline))
void			array_sort(t_array *array, t_cmpf cmpf)
{
	array_sort_impl(array, array->begin,
			array->end - array->element_size,
			cmpf);
}
