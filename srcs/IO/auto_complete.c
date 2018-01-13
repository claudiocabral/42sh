/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/13 17:47:15 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <io.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <environment.h>

int			is_separator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
}

void		auto_complete_push(t_array *array, char *base, char *candidate)
{
	size_t	ret;

	if (!base || !candidate)
		return ;
	if ((!*base || (ret = ft_strnequ(base, candidate, ft_strlen(base))))
			&& !array_find(array, &candidate, (t_cmpf )&ft_strcmp_wrapper))
		ret = (size_t)array_push_back(array, &candidate);
	else
	{
		free(candidate);
		return ;
	}
	if (!ret)
		free(candidate);
}

int			first_word(t_string *str)
{
	int		i;
	int		count;

	i = 0;
	count = -1;
	while ((unsigned long)i < str->size)
	{
		++count;
		while (ft_is_whitespace(str->buffer[i]))
			++i;
		while (str->buffer[i] && !ft_is_whitespace(str->buffer[i]))
		{
			++i;
			if (is_separator(str->buffer[i - 1]))
				count = 0;
		}
	}
	return (!count);
}

DIR			*get_dir(char *path, char **str)
{
	DIR		*dir;
	char	*dir_path;
	char	*begin;

	if (!(begin = ft_strrchr(path, ' ')))
		begin = path;
	else
		++begin;
	if ((dir_path = ft_strrchr(begin, '/')))
	{
		if (dir_path == begin)
			begin = "/";
		else
			dir_path[0] = 0;
		dir = opendir(begin);
		*dir_path = '/';
		*str = ft_strdup(dir_path + 1);
	}
	else
	{
		dir = opendir(".");
		*str = ft_strdup(begin);
	}
	return (dir);
}

int			is_directory_symlink(struct dirent *entry)
{
	DIR		*dir;
	char	buff[2048];

	if (entry->d_type != DT_LNK)
		return (0);
	readlink(entry->d_name, buff, 2048);
	if (!(dir = opendir(buff)))
		return (0);
	closedir(dir);
	return (1);
}

void		search_dir(DIR *dir, char *str, t_array *array)
{
	char			*candidate;
	struct dirent	*entry;

	entry = readdir(dir);
	if (ft_strequ(entry->d_name, "."))
		entry = readdir(dir);
	if (ft_strequ(entry->d_name, ".."))
		entry = readdir(dir);
	while (1)
	{
		if (!(candidate = malloc(sizeof(char)
						* (ft_strlen(entry->d_name) + 2))))
			break ;
		candidate[0] = 0;
		ft_strcat(candidate, entry->d_name);
		if (entry->d_type == DT_DIR || is_directory_symlink(entry))
			ft_strcat(candidate, "/");
		auto_complete_push(array, str, candidate);
		if (!(entry = readdir(dir)))
			break ;
	}
	closedir(dir);
}

char		*auto_complete_path(t_array *array, t_terminal *terminal)
{
	DIR				*dir;
	char			*str;

	if (!(dir = get_dir(terminal->line->buffer, &str)))
		return (0);
	search_dir(dir, str, array);
	return (str);
}

void		search_builtins(char *str, t_array *array)
{
	auto_complete_push(array, str, ft_strdup("cd"));
	auto_complete_push(array, str, ft_strdup("echo"));
	auto_complete_push(array, str, ft_strdup("pwd"));
	auto_complete_push(array, str, ft_strdup("env"));
	auto_complete_push(array, str, ft_strdup("setenv"));
	auto_complete_push(array, str, ft_strdup("unsetenv"));
}

char		*auto_complete_command(t_array *array, t_terminal *terminal)
{
	char	*path;
	char	*path_end;
	char	*str;
	DIR		*dir;

	if (!(path = ft_getenv("PATH")))
		return (0);
	if ((str = ft_strrchr(terminal->line->buffer, ' ')))
	{
		++str;
		while (is_separator(*str))
			++str;
		str = ft_strdup(str);
	}
	else
		str = ft_strdup(terminal->line->buffer);
	search_builtins(str, array);
	while (*path && (path_end = ft_strchr(path, ':')))
	{
		*path_end = 0;
		if (!(dir = opendir(path)))
			return (0);
		search_dir(dir, str, array);
		*path_end = ':';
		path = path_end + 1;
	}
	return (str);
}

void		choose_possibility(t_array *array, char *str,
		t_terminal *terminal)
{
	char	**it;
	char	*candidate;
	int		size;
	int		max_size;

	it = (char **)array->begin;
	if (it == array->end)
		return ;
	max_size = ft_strlen(*it);
	candidate = *it;
	while (it != array->end)
	{
		size = 0;
		while (size < max_size && (*it)[size] == candidate[size])
			++size;
		max_size = size;
		++it;
	}
	max_size = candidate[size];
	candidate[size] = 0;
	if (str)
		terminal_insert_string(terminal,
				candidate + ft_strlen(str));
	candidate[size] = (char)max_size;
}

int			auto_complete(t_terminal *terminal, int c)
{
	t_array			*array;
	char			*str;
	char			*begin;

	(void)c;
	str = 0;
	if (terminal->line->size == 0)
		return (1);
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	if (!first_word(terminal->line))
		str = auto_complete_path(array, terminal);
	else
	{
		begin = ft_strrchr(terminal->line->buffer, ' ');
		if (ft_strchr(begin == 0 ? terminal->line->buffer : begin, '/'))
			str = auto_complete_path(array, terminal);
		else
			str = auto_complete_command(array, terminal);
	}
	if (str && array_size(array) == 1)
		terminal_insert_string(terminal,
				*(char **)array->begin + ft_strlen(str));
	else if (str)
		choose_possibility(array, str, terminal);
	free(str);
	array_free(array, (t_freef) &free_wrapper);
	return (1);
}
