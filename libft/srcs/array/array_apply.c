/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:50:07 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 11:12:30 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>

void			array_apply(t_array *array, void *args, t_applyf applyf)
{
	unsigned char	*it;

	it = (unsigned char *)array->begin;
	while (it != (unsigned char *)array->end)
	{
		applyf(it, args);
		it += array->element_size;
	}
}

void			array_apply_reverse(t_array *array, void *args, t_applyf applyf)
{
	unsigned char	*it;

	it = (unsigned char *)array->end - array->element_size;
	while (it != (unsigned char *)array->begin)
	{
		applyf(it, args);
		it -= array->element_size;
	}
	applyf(it, args);
}

void	array_swap(t_array *array, void *a, void *b)
{
	ft_memcpy(array->end, a, array->element_size);
	ft_memcpy(a, b, array->element_size);
	ft_memcpy(b, array->end, array->element_size);
	ft_bzero(array->end, array->element_size);
}

int		array_partition(t_array *array, int low, int high, t_cmpf cmpf)
{
	int					i;
	int					j;
	unsigned char const	*pivot;

	pivot = array->begin + high;
	i = low - array->element_size;
	j = low;
	while (j < high)
	{
		if (cmpf(array->begin + j, pivot) < 0)
		{
			i += array->element_size;
			array_swap(array, array->begin + i, array->begin + j);
		}
		j += array->element_size;
	}
	if (cmpf(array->begin + high, array->begin + i + array->element_size) < 0)
		array_swap(array, array->begin + i + array->element_size,
												array->begin + high);
	return (i + array->element_size);
}

void			array_sort(t_array *array, int low, int high, t_cmpf cmpf)
{
	int	p;

	if (low < high)
	{
		p = array_partition(array, low, high, cmpf);
		array_sort(array, low, p - array->element_size, cmpf);
		array_sort(array, p + array->element_size, high, cmpf);
	}
}
