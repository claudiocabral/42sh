/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_name_lookup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:48:51 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/12 11:51:14 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>
#include <hash_table.h>
#include <builtins.h>
#include <execute.h>

static	t_array			*g_paths;

void					free_paths(t_array *paths)
{
	t_binary_path	**it;

	if (!paths)
		return ;
	it = (t_binary_path **)paths->begin;
	while (it != paths->end)
	{
		hash_table_free((*it)->table, (t_freef) & free_wrapper);
		string_free((*it)->buffer);
		free(*it);
		++it;
	}
	free(paths->begin);
	free(paths);
}

int						generate_paths(void)
{
	free_paths(g_paths);
	g_paths = 0;
	return (init_paths(&g_paths));
}

int						init_path_table(void)
{
	ZERO_IF_FAIL(init_builtins());
	return (generate_paths());
}

char const				*command_name_lookup(char const *name)
{
	t_binary_path	**path;
	char const		**entry;

	path = g_paths->begin;
	while (path != g_paths->end)
	{
		if ((entry = hash_table_find((*path)->table, &name)))
		{
			binary_path_set_buffer(*path, *entry);
			return ((*path)->buffer->buffer);
		}
		++path;
	}
	return (0);
}
