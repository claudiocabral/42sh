/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_replace.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 14:45:45 by ccabral           #+#    #+#             */
/*   Updated: 2018/03/23 16:44:43 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_string.h>

int			string_find(t_string *str, char const *target)
{
	char	*ptr;

	ptr = ft_strstr(str->buffer, target);
	if (!ptr)
		return (-1);
	return (ptr - str->buffer);
}

int			string_replace(t_string *str, char const *search,
											char const *replace)
{
	int	pos;
	int	i;
	int	size;

	if (ft_strequ(search, replace))
		return (0);
	i = 0;
	size = ft_strlen(search);
	while ((pos = string_find(str, search)) >= 0)
	{
		string_delete_n(str, pos, size);
		string_insert_string(str, replace, pos);
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
