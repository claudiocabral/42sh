/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:49:51 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/05 11:12:03 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARRAY_H
# define ARRAY_H

#include <libft.h>

typedef struct	s_array
{
	void	*begin;
	void	*end;
	size_t	element_size;
	size_t	capacity;
}				t_array;

t_array			*array_create(size_t element_size, size_t nbr_elements);
void			array_clear(t_array *array, t_freef free_func);
void			array_free(t_array *array, t_freef free_func);
int				array_increase_capacity(t_array *array);
void			*array_push_back(t_array *array, void *element);
void			array_apply(t_array *array, void *args, t_applyf);
void			array_apply_reverse(t_array *array, void *args, t_applyf);
void			array_sort(t_array *array, int low, int high, t_cmpf cmpf);

#endif
