/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:06:40 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/11 16:48:48 by ccabral          ###   ########.fr       */
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
	array->end = (unsigned char *)array->begin;
	array->element_size = element_size;
	ft_bzero(array->begin, array->capacity + element_size);
	return (array);
}

t_array			*array_copy(t_array const *src, void *args,
										t_cpyf cpyf, t_freef freef)
{
	t_array	*dst;
	void	*src_it;

	ZERO_IF_FAIL(dst = array_create(src->element_size,
					src->capacity / src->element_size));
	src_it = src->begin;
	while (src_it != src->end)
	{
		if (!cpyf(dst->end, src_it, args))
		{
			array_free(dst, freef);
			return (0);
		}
		src_it += src->element_size;
		dst->end += src->element_size;
	}
	return (dst);
}

void			array_clear(t_array *array, t_freef free_func)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		free_func(it);
		it += array->element_size;
	}
	ft_bzero(array->begin, array->end - array->begin);
	array->end = array->begin;
}

void			array_free(t_array *array, t_freef free_func)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		free_func(it);
		it += array->element_size;
	}
	free(array->begin);
	free(array);
}

int				array_increase_capacity(t_array *array)
{
	void	*buffer;

	if (!(buffer = malloc(array->capacity * 2)))
		return (0);
	ft_memcpy(buffer, array->begin, array->capacity);
	free(array->begin);
	array->end = buffer + (array->end - array->begin);
	array->begin = buffer;
	array->capacity += array->capacity;
	return (1);
}
