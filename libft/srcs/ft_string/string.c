/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:46:52 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/22 14:46:33 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_string.h>
#include <stdlib.h>
#include <libft.h>

t_string	*string_create(size_t capacity)
{
	t_string	*string;

	capacity += !capacity;
	if (!(string = (t_string *)malloc(sizeof(t_string) * capacity)))
		return (0);
	if (!string_init(string, capacity))
	{
		free(string);
		return (0);
	}
	return (string);
}

t_string	*string_init(t_string *string, size_t capacity)
{
	if (!(string->buffer = (char *)malloc(sizeof(char) * capacity)))
		return (0);
	string->capacity = capacity;
	string->size = 0;
	ft_bzero(string->buffer, string->capacity);
	return (string);
}

t_string	*string_insert(t_string *string, char c, size_t pos)
{
	if (pos > string->size)
		pos = string->size;
	if (string->size + 1 >= string->capacity)
		string->capacity = ft_realloc((void **)&(string->buffer),
				string->capacity, string->capacity * 2);
	if (!string->buffer)
		return (0);
	if (pos != string->size)
		ft_memmove(string->buffer + pos + 1,
				string->buffer + pos, string->size - pos);
	string->buffer[pos] = c;
	string->size++;
	string->buffer[string->size] = 0;
	return (string);
}

t_string	*string_destructive_insert(t_string *string, char *where,
													char const *what)
{
	size_t	size;

	size = ft_strlen(what) + 1;
	if ((where + size) >= string->buffer + string->capacity)
		string->capacity = ft_realloc((void **)&(string->buffer),
				string->capacity, (string->capacity + size) * 2);
	if (!string->buffer)
		return (0);
	ft_memcpy(where, what, size);
	return (string);
}
