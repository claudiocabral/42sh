/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring_buffer.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:18:48 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/07 11:53:08 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RING_BUFFER_H
# define RING_BUFFER_H

# include <libft.h>

typedef struct	s_ring_buffer
{
	void	*begin;
	void	*current;
	void	*next;
	size_t	element_size;
	size_t	capacity;
	t_freef	clearf;
}				t_ring_buffer;

t_ring_buffer	*ring_buffer_create(size_t element_size, size_t nbr_elements,
										t_freef cleanf);
t_ring_buffer	*ring_buffer_init(t_ring_buffer *buffer, size_t size,
								void *(*initf)(void *, size_t), t_freef freef);
void			ring_buffer_free(t_ring_buffer *buffer, t_freef freef);
void			*ring_buffer_push_back(t_ring_buffer *buffer, void *element,
											void *(*cpy)(void *, void const *));
void			*ring_buffer_push_empty(t_ring_buffer *buffer);
void			*ring_buffer_previous(t_ring_buffer *buffer);
void			*ring_buffer_next(t_ring_buffer *buffer);

#endif
