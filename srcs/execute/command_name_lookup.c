/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_name_lookup.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/10 11:48:51 by claudioca         #+#    #+#             */
/*   Updated: 2017/12/15 22:27:15 by claudioca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <array.h>
#include <hash_table.h>
#include <builtins.h>
#include <execute.h>

static	t_hash_table	*g_builtins;
static	t_array			*g_paths;

uint64_t				builtin_hash(t_builtin *builtin)
{
	return (hash_string(&builtin->name));
}

int						builtin_compare(t_builtin *a, t_builtin *b)
{
	return (ft_strcmp(a->name, b->name));
}

int						init_path_table(void)
{
	t_builtin	builtin;

	ZERO_IF_FAIL(g_builtins = hash_table_create(sizeof(t_builtin), 5,
					(t_hashf)&builtin_hash, (t_cmpf)&builtin_compare));
	builtin.name = "cd";
	builtin.func = &cd;
	hash_table_insert(g_builtins, &builtin);
	builtin.name = "echo";
	builtin.func = &echo;
	hash_table_insert(g_builtins, &builtin);
	init_paths(&g_paths);
	return (1);
}

__attribute__((always_inline))
t_builtin				*get_builtin_command(char const *name)
{
	t_builtin	dummy;

	dummy.name = name;
	return (hash_table_find(g_builtins, &dummy));
}

__attribute__((always_inline))
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
	return(0);
}
