/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/09 12:12:27 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/09 12:23:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>

void	*array_find(t_array *array, void *data, t_cmpf cmpf)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		if (cmpf(data, it) == 0)
			return (it);
		it += array->element_size;
	}
	return (0);
}
