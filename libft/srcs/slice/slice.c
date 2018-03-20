/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slice.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 14:32:42 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/20 14:33:29 by ccabral          ###   ########.fr       */
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
