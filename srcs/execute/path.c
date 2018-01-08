/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 13:50:55 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/08 18:24:12 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <array.h>
#include <hash_table.h>
#include <execute.h>
#include <environment.h>
#include <ft_printf.h>

int	ft_strcmp_pointer(char **a, char **b)
{
	return (ft_strcmp(*a, *b));
}

t_string		*binary_path_set_buffer(t_binary_path *path, char const *suffix)
{
	char	*point;

	point = ft_strrchr(path->buffer->buffer, '/') + 1;
	return (string_destructive_insert(path->buffer, point, suffix));
}

int				fill_table(t_binary_path *path)
{
	DIR				*dir;
	struct dirent	*entry;
	char			*tmp;

	ZERO_IF_FAIL(dir = opendir(path->name));

	entry = readdir(dir);
	while(entry && (ft_strequ(entry->d_name, ".")
				|| ft_strequ(entry->d_name, "..")))
		entry = readdir(dir);
	while (entry)
	{
		tmp = ft_strdup(entry->d_name);
		hash_table_insert(path->table, &tmp);
		entry = readdir(dir);
	}
	closedir(dir);
	return (1);
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
							(t_hashf)&hash_string, (t_cmpf)&ft_strcmp_pointer)))
	{
		string_free(path->buffer);
		free(path);
		return (0);
	}
	fill_table(path);
	return (path);
}

void	hash_and_print(char **item, t_hash_table *table)
{
	ft_printf("%llu\t%s\n", table->hash(item), *item);
}

int	hash_paths(t_array *paths)
{
	char			*begin;
	char			*end;
	t_binary_path	*tmp;

	ZERO_IF_FAIL(begin = ft_getenv("PATH"));
	ft_printf("got this far...\n");
	while ((end = ft_strchr(begin, ':')))
	{
		tmp = make_path_entry(begin, end - begin);
		array_push_back(paths, &tmp);
		begin = end + 1;
	}
	tmp = make_path_entry(begin, ft_strlen(begin));
	array_push_back(paths, &tmp);
	return (1);
}

int		init_paths(t_array **paths)
{
	ZERO_IF_FAIL(*paths = array_create(sizeof(t_binary_path *), 8));
	return (hash_paths(*paths));
}
