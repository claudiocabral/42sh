/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_entry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccabral <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 11:59:47 by ccabral           #+#    #+#             */
/*   Updated: 2018/01/12 12:02:38 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <execute.h>
#include <hash_table.h>

static int		ft_strcmp_pointer(char **a, char **b)
{
	return (ft_strcmp(*a, *b));
}

t_binary_path	*make_path_entry(char const *name, size_t size)
{
	t_binary_path	*path;

	ZERO_IF_FAIL(path = (t_binary_path *)malloc(sizeof(t_binary_path)
													+ size + 2));
	path->name = (char *)path + sizeof(t_binary_path);
	ft_strncpy(path->name, name, size);
	path->name[size] = '/';
	path->name[size + 1] = '\0';
	if (!(path->buffer = string_create(size * 2 + 2)))
	{
		free(path);
		return (0);
	}
	string_destructive_insert(path->buffer, path->buffer->buffer, path->name);
	if (!(path->table = hash_table_create(sizeof(char *), 2048,
					(t_hashf) & hash_string, (t_cmpf) & ft_strcmp_pointer)))
	{
		string_free(path->buffer);
		free(path);
		return (0);
	}
	fill_table(path);
	return (path);
}
