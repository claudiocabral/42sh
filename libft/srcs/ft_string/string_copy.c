/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/21 16:59:22 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/22 14:05:36 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <ft_string.h>
#include <libft.h>

t_string	*string_copy(t_string *dst, t_string const *src)
{
	if (dst->capacity < src->capacity)
	{
		free(dst->buffer);
		if (!(dst->buffer = (char *)malloc(sizeof(char) * src->capacity)))
			return (0);
		dst->capacity = src->capacity;
	}
	ft_memcpy(dst->buffer, src->buffer, src->size + 1);
	dst->size = src->size;
	return (dst);
}

t_string	*string_copy_n(t_string *dst, t_string const *src, size_t n)
{
	if (dst->capacity < src->capacity)
	{
		free(dst->buffer);
		if (!(dst->buffer = (char *)malloc(sizeof(char) * src->capacity)))
			return (0);
		dst->capacity = src->capacity;
	}
	if (n > src->size)
		n = src->size;
	ft_memcpy(dst->buffer, src->buffer, n);
	dst->buffer[n] = 0;
	dst->size = n;
	return (dst);
}

t_string	*string_append(t_string *dst, char const *src)
{
	while (*src)
	{
		string_insert(dst, *src, dst->size);
		++src;
	}
	return (dst);
}

t_string	*string_append_char(t_string *dst, char c)
{
	string_insert(dst, c, dst->size);
	return (dst);
}
