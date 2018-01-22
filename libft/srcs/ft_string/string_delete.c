/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_delete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/11 16:51:13 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/22 14:37:48 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>
#include <ft_string.h>

void		string_delete(t_string *string, size_t pos)
{
	if (!string->buffer[0] || pos >= string->size)
		return ;
	ft_memmove(string->buffer + pos, string->buffer + pos + 1,
											string->size - pos);
	string->size--;
}

void		string_clear(t_string *string)
{
	ft_bzero(string->buffer, string->capacity);
	string->size = 0;
}

void		string_free_content(t_string *string)
{
	if (!string)
		return ;
	free(string->buffer);
	string->buffer = 0;
	string->size = 0;
	string->capacity = 0;
}

void		string_free(t_string *string)
{
	string_free_content(string);
	free(string);
}
