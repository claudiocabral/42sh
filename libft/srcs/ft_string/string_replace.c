/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:45:45 by ccabral           #+#    #+#             */
/*   Updated: 2018/06/10 17:23:30 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_string.h>

int			string_find(t_string *str, char const *target, int pos)
{
	char	*ptr;

	ptr = ft_strstr(str->buffer + pos, target);
	if (!ptr)
		return (-1);
	return (ptr - str->buffer);
}

int			string_replace(t_string *str, char const *search,
											char const *replace)
{
	int	pos;
	int	init_pos;
	int	size;

	if (ft_strequ(search, replace))
		return (0);
	size = ft_strlen(search);
	init_pos = 0;
	while ((pos = string_find(str, search, init_pos)) >= 0)
	{
		string_delete_n(str, pos, size);
		string_insert_string(str, replace, pos);
		init_pos = pos + ft_strlen(replace);
	}
	return (1);
}

t_string	*string_insert_string(t_string *string,
									char const *source, int pos)
{
	int	i;

	i = 0;
	while (source[i])
	{
		string_insert(string, source[i], pos + i);
		++i;
	}
	return (string);
}
