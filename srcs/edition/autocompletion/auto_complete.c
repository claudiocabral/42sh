/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/17 11:57:19 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mysh.h>

char		*auto_complete_path(t_array *array, char *line)
{
	DIR				*dir;
	char			*str;

	if (!(dir = get_dir(line, &str)))
		return (0);
	search_dir(dir, str, array);
	return (str);
}

void		search_builtins(char *str, t_array *array)
{
	auto_complete_push(array, str, ft_strdup("cd"));
	auto_complete_push(array, str, ft_strdup("echo"));
	auto_complete_push(array, str, ft_strdup("env"));
	auto_complete_push(array, str, ft_strdup("exit"));
	auto_complete_push(array, str, ft_strdup("pwd"));
	auto_complete_push(array, str, ft_strdup("setenv"));
	auto_complete_push(array, str, ft_strdup("unsetenv"));
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

	// ft_printf("LINE == %s$\n", line);
	if (ft_strlen(line) == 0)
		return (0);
	ZERO_IF_FAIL(array = array_create(8, sizeof(char *)));
	if (!first_word(line))
	{
		// ft_printf("first word\n");
		str = auto_complete_path(array, line);
	}
	else
	{
		begin = ft_strrchr(line, ' ');
		if (ft_strchr(begin == 0 ? line : begin, '/'))
			str = auto_complete_path(array, line);
		else
			str = auto_complete_command(array, line);
	}
	// ft_printf("AUTOCOMPLETE == %s\n", array->begin);
	// char **it;
    //
	// it = (char **)array->begin;
	// while (it != array->end)
	// {
		// ft_printf("IT == %s\n", *it);
	// 	it++;
	// }
	if (str && array_size(array) == 1)
		return (*(char **)array->begin + ft_strlen(str));
	// else if (str)
	// 	choose_possibility(array, str, terminal);
	free(str);
	array_free(array, (t_freef) & free_wrapper);
	return (NULL);
}