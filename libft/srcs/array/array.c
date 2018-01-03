/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 16:06:40 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/03 09:45:12 by claudioca        ###   ########.fr       */
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
	void	**it;

	it = array->begin;
	while (it != array->end)
	{
		free_func(*it);
		ft_bzero(it, array->element_size);
		it = it + array->element_size;
	}
	array->end = array->begin;
}

void			array_free(t_array *array, t_freef free_func)
{
	void	**it;

	it = array->begin;
	while (it != array->end)
	{
		free_func(*it);
		it = (void *)it + array->element_size;
	}
	free(array->begin);
	free(array);
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

void			*median(void *begin, void *end, size_t size)
{
	return (begin + ((size_t)(end - begin) / (size * 2)) * size);
}

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
