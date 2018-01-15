/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: claudiocabral <cabral1349@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/05 10:51:53 by claudioca         #+#    #+#             */
/*   Updated: 2018/01/15 13:08:23 by ccabral          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <io.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include <environment.h>
#include <ft_printf.h>

int			is_separator(char c)
{
	return (c == '|' || c == '&' || c == ';' || c == '<' || c == '>');
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
	auto_complete_push(array, str, ft_strdup("env"));
	auto_complete_push(array, str, ft_strdup("exit"));
	auto_complete_push(array, str, ft_strdup("pwd"));
	auto_complete_push(array, str, ft_strdup("setenv"));
	auto_complete_push(array, str, ft_strdup("unsetenv"));
}

char		*auto_complete_command(t_array *array, t_terminal *terminal)
{
	char	*path;
	char	*path_end;
	char	*str;
	DIR		*dir;

	ZERO_IF_FAIL(path = ft_getenv("PATH"));
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
		ZERO_IF_FAIL(dir = opendir(path));
		search_dir(dir, str, array);
		*path_end = ':';
		path = path_end + 1;
	}
	return (str);
}

int			auto_complete(t_terminal *terminal, int c)
{
	t_array			*array;
	char			*str;
	char			*begin;

	if (terminal->line->size == 0)
		return (c != 0);
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
		terminal_insert_string(terminal, *(char **)array->begin
												+ ft_strlen(str));
	else if (str)
		choose_possibility(array, str, terminal);
	free(str);
	array_free(array, (t_freef) & free_wrapper);
	return (1);
}
