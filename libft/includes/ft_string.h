/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:47:38 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/06 10:32:32 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

#include <stddef.h>

typedef struct	s_string
{
	char	*buffer;
	size_t	size;
	size_t	capacity;
}				t_string;

t_string	*string_create(size_t capacity);
t_string	*string_init(t_string *string, size_t capacity);
t_string	*string_insert(t_string *string, char c, size_t pos);
void		string_delete(t_string *string,  size_t pos);
void		string_clear(t_string *string);
t_string	*string_copy(t_string *dst, t_string const *src);
void		string_free(t_string *string);
void		string_free_content(t_string *string);

#endif
