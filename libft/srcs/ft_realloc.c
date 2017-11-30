/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/06 13:31:24 by ccabral           #+#    #+#             */
/*   Updated: 2017/11/06 17:42:32 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

#include "libft.h"

size_t	ft_realloc(void **buffer, size_t old_size,
		size_t new_size)
{
	void	*new_buffer;

	if (!(new_buffer = malloc(new_size)))
		return (0);
	if (*buffer)
	{
		ft_memcpy(new_buffer, *buffer, old_size);
		free(*buffer);
	}
	*buffer = new_buffer;
	return (new_size);
}
