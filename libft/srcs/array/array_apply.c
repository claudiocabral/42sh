/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_apply.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 10:50:07 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 14:22:34 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>

void			array_apply(t_array *array, void *args, t_applyf applyf)
{
	void	*it;

	it = array->begin;
	while (it != array->end)
	{
		applyf(it, args);
		it += array->element_size;
	}
}

void			array_apply_reverse(t_array *array, void *args, t_applyf applyf)
{
	void	*it;

	if (array->begin == array->end)
		return ;
	it = array->end - array->element_size;
	while (it != array->begin)
	{
		applyf(it, args);
		it -= array->element_size;
	}
	applyf(it, args);
}

void			*array_apply_until(t_array *array, void *args,
											t_applyf_until applyf)
{
	void	*it;
	void	*val;

	it = array->begin;
	while (it != array->end)
	{
		if ((val = applyf(it, args)))
			return (val);
		it += array->element_size;
	}
	return (0);
}

int				array_size(t_array *array)
{
	return ((array->end - array->begin) / array->element_size);
}
