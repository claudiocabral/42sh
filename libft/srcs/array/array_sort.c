/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 16:59:31 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:44:39 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>
#include <libft.h>

void			*array_find_sorted(t_array *array, void const *element,
															t_cmpf cmpf)
{
	void	*begin;
	void	*end;
	void	*middle;
	int		result;

	begin = array->begin;
	end = array->end;
	middle = median(begin, end, array->element_size);
	while (end > begin)
	{
		if ((result = cmpf(element, middle)) == 0)
			return (middle);
		else if (result > 0)
		{
			if (begin == middle)
				return (0);
			begin = middle;
			middle = median(begin, end, array->element_size);
		}
		else if (result < 0)
		{
			if (end == middle)
				return (0);
			end = middle;
			middle = median(begin, end, array->element_size);
		}
	}
	return (0);
}

void			*array_find_insertion_point(t_array *array, void const *element,
																	t_cmpf cmpf)
{
	void	*begin;
	void	*end;
	void	*middle;
	int		result;

	begin = array->begin;
	end = array->end;
	middle = median(begin, end, array->element_size);
	while (end > begin)
	{
		if ((result = cmpf(element, middle)) == 0)
			return (middle);
		else if (result > 0)
		{
			if (begin == middle)
				break ;
			begin = middle;
			middle = median(begin, end, array->element_size);
		}
		else if (result < 0)
		{
			if (end == middle)
				return (begin);
			end = middle;
			middle = median(begin, end, array->element_size);
		}
	}
	return (begin);
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
			ft_swap(i, j, array->end, array->element_size);
		}
		j += array->element_size;
	}
	i += array->element_size;
	if (cmpf(high, i) < 0)
		ft_swap(i, high, array->end, array->element_size);
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

__attribute__((always_inline))
void			array_sort(t_array *array, t_cmpf cmpf)
{
	array_sort_impl(array, array->begin,
			array->end - array->element_size,
			cmpf);
}
