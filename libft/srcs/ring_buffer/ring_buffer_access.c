/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:57:59 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 13:07:06 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ring_buffer.h>

void			*ring_buffer_previous(t_ring_buffer *buffer, size_t n)
{
	size_t	index_zero;

	n *= buffer->element_size;
	index_zero = buffer->current - buffer->begin;
	while (n >= buffer->capacity)
		n -= buffer->capacity;
	return (index_zero > n ? buffer->current - n
			: buffer->current + (buffer->capacity - (n - index_zero)));
}

void			*ring_buffer_next(t_ring_buffer *buffer, size_t n)
{
	size_t	index_zero;

	n *= buffer->element_size;
	index_zero = buffer->current - buffer->begin;
	while (n + index_zero >= buffer->capacity)
		n -= buffer->capacity;
	return (buffer->current + n);
}
