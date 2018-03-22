/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:32:42 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/22 16:13:31 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <slice.h>

t_slice	make_slice(char const *ptr, int size)
{
	t_slice	slice;

	slice.ptr = ptr;
	slice.size = size;
	return (slice);
}

t_slice	error_slice(void)
{
	t_slice slice;

	slice.ptr = 0;
	slice.size = 0;
	return (slice);
}

t_slice	slice_from_pointers(char const *begin, char const *end)
{
	t_slice	slice;

	slice.ptr = begin;
	slice.size = end - begin;
	return (slice);
}
