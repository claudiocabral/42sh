/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/05 17:47:38 by claudioca         #+#    #+#             */
/*   Updated: 2018/05/11 11:42:30 by ctrouill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STRING_H
# define FT_STRING_H

# include <stddef.h>

typedef struct	s_string
{
	char	*buffer;
	size_t	size;
	size_t	capacity;
}				t_string;

t_string		*string_create(size_t capacity);
t_string		*string_init(t_string *string, size_t capacity);
t_string		*string_insert(t_string *string, char c, size_t pos);
t_string		*string_insert_string(t_string *string,
									char const *source, int pos);
t_string		*string_destructive_insert(t_string *string, char *where,
														char const *what);
void			string_delete(t_string *string, size_t pos);
void			string_delete_n(t_string *string, size_t pos, size_t size);
void			string_clear(t_string *string);
t_string		*string_copy(t_string *dst, t_string const *src);
t_string		*string_copy_n(t_string *dst, t_string const *src, size_t n);
void			string_free(t_string *string);
void			string_free_content(t_string *string);
t_string		*string_append_char(t_string *dst, char c);
t_string		*string_append_n(t_string *dst, char const *str, int n);
t_string		*string_append(t_string *dst, char const *src);
int				string_replace(t_string *str, char const *search,
												char const *replace);
int				string_find(t_string *str, char const *target);
char			*ft_strtok(char *str, const char *delim);

#endif
