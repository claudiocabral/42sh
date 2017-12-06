/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer_access.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 11:57:59 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/06 13:45:50 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ring_buffer.h>

void			*ring_buffer_previous(t_ring_buffer *buffer)
{
	void	*entry;

	entry = buffer->current;
	if (buffer->current == buffer->begin)
			buffer->current =
				buffer->begin + buffer->capacity - buffer->element_size;
	else
		buffer->current -= buffer->element_size;
	return (entry);
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
	return (buffer->current + buffer->element_size);
}
