/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:57:59 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 16:20:29 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ring_buffer.h>

void			*ring_buffer_previous(t_ring_buffer *buffer)
{
	if (buffer->current == buffer->first)
		return (buffer->current);
	if (buffer->current == buffer->begin)
		buffer->current =
			buffer->begin + buffer->capacity - buffer->element_size;
	else
		buffer->current -= buffer->element_size;
	return (buffer->current);
}

void			*ring_buffer_next(t_ring_buffer *buffer)
{
	if (buffer->current ==
			buffer->begin + buffer->capacity - buffer->element_size)
		buffer->current = buffer->begin;
	else if (buffer->current + buffer->element_size == buffer->next)
		return (buffer->next);
	else
		buffer->current += buffer->element_size;
	return (buffer->current);
}

void			*ring_buffer_push_empty(t_ring_buffer *buffer)
{
	buffer->current = buffer->next;
	buffer->clearf(buffer->current);
	buffer->next = (buffer->next + buffer->element_size
			>= buffer->begin + buffer->capacity)
		? buffer->begin
		: buffer->next + buffer->element_size;
	buffer->clearf(buffer->next);
	if (buffer->next < buffer->first)
		buffer->first = buffer->next;
	return (buffer->current);
}
