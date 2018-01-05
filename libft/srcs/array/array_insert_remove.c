/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_insert_remove.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:42:09 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/05 10:43:41 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <array.h>

void			*array_push_back(t_array *array, void *element)
{
	if (array->capacity <= array->end - array->begin + array->element_size
		 && !array_increase_capacity(array))
		return (0);
	ft_memcpy(array->end, element, array->element_size);
	array->end = (unsigned char *)array->end + array->element_size;
	ft_bzero(array->end, array->element_size);
	return ((unsigned char *)array->end - array->element_size);
}

void			*array_insert(t_array *array, void *where, void *element)
{
	if (array->capacity <= array->end - array->begin + array->element_size
		 && !array_increase_capacity(array))
		return (0);
	ft_memmove(where + array->element_size, where, array->end - where);
	ft_memcpy(where, element, array->element_size);
	array->end += array->element_size;
	ft_bzero(array->end, array->element_size);
	return (where);
}

void			*array_insert_sorted(t_array *array, void *element,
		t_cmpf cmpf)
{
	void	*insertion_point;
	if (array->capacity <= array->end - array->begin + array->element_size
			&& !array_increase_capacity(array))
		return (0);
	insertion_point = array_find_insertion_point(array, element, cmpf);
	return (array_insert(array, insertion_point, element));
}

void			array_remove(t_array *array, void *element, t_freef freef)
{
	freef(element);
	ft_memmove(element, element + array->element_size,
						array->end - element);
	array->end -= array->element_size;
}

void			array_remove_if(t_array *array, void const *data,
											t_freef freef, t_predf predicate)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		if (predicate(it, data))
		{
			array_remove(array, it, freef);
			continue ;
		}
		it += array->element_size;
	}
}
