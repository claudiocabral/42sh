/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 15:49:51 by claudioca         #+#    #+#             */
/*   Updated: 2017/11/30 16:15:39 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#ifndef ARRAY_H
# define ARRAY_H

typedef struct	s_array
{
	void	*begin;
	void	*end;
	size_t	element_size;
	size_t	capacity;
}				t_array;

typedef void	(*t_freef)(void *element);

t_array			*array_create(size_t element_size, size_t nbr_elements);
void			array_clear(t_array *array, t_freef free_func);
void			array_free(t_array *array, t_freef free_func);
void			*array_push_back(t_array *array, void *element);
void			*array_apply(size_t element_size, size_t nbr_elements);
void			*array_apply_reverse(size_t element_size, size_t nbr_elements);
void			*array_sort(t_array *array, t_cmpf cmpf);

#endif
