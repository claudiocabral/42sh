/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:13:27 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 15:58:01 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ring_buffer.h>
#include <stdlib.h>

t_ring_buffer	*ring_buffer_init(t_ring_buffer *buffer, size_t size,
							void *(*initf)(void *, size_t), t_freef freef)
{
	void	*it;
	void	*end;

	it = buffer->begin;
	end = buffer->begin + buffer->capacity;
	while (it != end)
	{
		if (!initf(it, size))
		{
			ring_buffer_free(buffer, freef);
			return (0);
		}
		it = (unsigned char *)it + buffer->element_size;
	}
	return (buffer);
}

t_ring_buffer	*ring_buffer_create(size_t element_size, size_t nbr_elements,
																t_freef clearf)
{
	t_ring_buffer	*buffer;

	if (!(buffer = malloc(sizeof(t_ring_buffer))))
		return (0);
	buffer->capacity = element_size * nbr_elements;
	if (!(buffer->begin = malloc(buffer->capacity)))
	{
		free(buffer);
		return (0);
	}
	buffer->element_size = element_size;
	buffer->first = buffer->begin;
	buffer->current = buffer->begin;
	buffer->next = buffer->begin;
	buffer->clearf = clearf;
	return (buffer);
}

void			ring_buffer_free(t_ring_buffer *buffer, t_freef freef)
{
	void	*it;
	void	*end;

	it = buffer->begin;
	end = buffer->begin + buffer->capacity;
	while (it != end)
	{
		freef(it);
		it = (unsigned char *)it + buffer->element_size;
	}
	free(buffer->begin);
	free(buffer);
}

void			ring_buffer_clean(t_ring_buffer *buffer, t_freef freef)
{
	void	*it;
	void	*end;

	it = buffer->begin;
	end = buffer->begin + buffer->capacity;
	while (it != end)
	{
		freef(it);
		it = it + buffer->element_size;
	}
	buffer->first = buffer->begin;
	buffer->current = buffer->begin;
	buffer->next = buffer->begin;
}

void			*ring_buffer_push_back(t_ring_buffer *buffer, void *element,
											void *(*cpy)(void *, void const*))
{
	cpy(buffer->next, element);
	buffer->current = buffer->next;
	buffer->next = (buffer->next + buffer->element_size
			>= buffer->begin + buffer->capacity)
		? buffer->begin
		: buffer->next + buffer->element_size;
	buffer->clearf(buffer->next);
	return (buffer->current);
}
