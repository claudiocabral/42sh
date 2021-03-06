/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/06/04 02:59:39 by gfloure          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

void		auto_complete_push(t_array *array, char *base, char *candidate)
{
	size_t	ret;

	if (!base || !candidate)
		return ;
	if ((!*base || (ret = ft_strnequ(base, candidate, ft_strlen(base))))
			&& !array_find(array, &candidate, (t_cmpf) & ft_strcmp_wrapper))
		ret = (size_t)array_push_back(array, &candidate);
	else
	{
		free(candidate);
		return ;
	}
}

char		*auto_complete_path(t_array *array, char *line)
{
	DIR				*dir;
	char			*str;

	if (!(dir = get_dir(line, &str)))
		return (0);
	search_dir(dir, str, array);
	return (str);
}

void		auto_complete_loop(t_array *array, char *path, char *str)
{
	char	*path_end;
	char	tmp;
	DIR		*dir;

	while (*path)
	{
		if (!(path_end = ft_strchr(path, ':')))
			path_end = ft_strchr(path, 0);
		tmp = *path_end;
		*path_end = 0;
		if (!(dir = opendir(path)))
			return ;
		search_dir(dir, str, array);
		*path_end = tmp;
		path = *path_end ? path_end + 1 : path_end;
	}
}

char		*auto_complete_command(t_array *array, char *line)
{
	char	*path;
	char	*str;

	path = ft_getenv_safe("PATH");
	if ((str = ft_strrchr(line, ' ')))
	{
		++str;
		while (is_separator(*str))
			++str;
		str = ft_strdup(str);
	}
	else
		str = ft_strdup(line);
	auto_complete_loop(array, path, str);
	search_builtins(str, array);
	return (str);
}

char		*auto_complete(char *line)
{
	t_array			*array;
	char			*str;
	char			*begin;

	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	if (!first_word(line))
		str = auto_complete_path(array, line);
	else
	{
		begin = ft_strrchr(line, ' ');
		if (ft_strchr(begin == 0 ? line : begin, '/'))
			str = auto_complete_path(array, line);
		else
			str = auto_complete_command(array, line);
	}
	begin = NULL;
	if (str && array_size(array) == 1)
	{
		begin = ft_strdup(*(char **)array->begin + ft_strlen(str));
		ft_strdel(&str);
	}
	else if (str && array_size(array) > 1)
		choose_possibility(array, str);
	array_free(array, (t_freef) & free_wrapper);
	return (begin);
}
