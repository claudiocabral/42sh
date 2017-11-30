/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:06:40 by claudioca         #+#    #+#             */
/*   Updated: 2017/11/30 16:21:31 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <array.h>

t_array			*array_create(size_t element_size, size_t nbr_elements)
{
	t_array	*array;

	if (!(array = malloc(sizeof(t_array))))
		return (0);
	array->capacity = element_size * nbr_elements;
	if (!(array->begin = malloc(array->capacity + element_size)))
	{
		free(array);
		return (0);
	}
	array->end = (unsigned char *)array->begin + element_size;
	array->element_size = element_size;
	array->end = 0;
	return (array);
}

void			array_clear(t_array *array, t_freef free_func)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		free_func(it);
		ft_memset(it, array->element_size, 0);
		it = (unsigned char *)it + array->element_size;
	}
	array->end = (unsigned char *)array->begin + array->element_size;
}
